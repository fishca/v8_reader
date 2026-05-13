//---------------------------------------------------------------------------

#ifndef MessageRegistrationH
#define MessageRegistrationH

#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

//---------------------------------------------------------------------------
enum MessageState
{
	msEmpty      = -1,
	msSuccesfull = 0,
	msWarning    = 1,
	msInfo       = 2,
	msError      = 3,
	msWait       = 4,
	msHint       = 5
};

//---------------------------------------------------------------------------
class MessageRegistrator
{
public:
	using Utf16String = std::u16string;
	using MessageParam = std::pair<Utf16String, Utf16String>;
	using MessageParams = std::vector<MessageParam>;

private:
	bool DebugMessage;

	template <typename...>
	using void_t = void;

	template <typename T, typename = void>
	struct HasCStr : std::false_type {};

	template <typename T>
	struct HasCStr<T, void_t<decltype(std::declval<const T&>().c_str())>> : std::true_type {};

	static void AppendPairs(MessageParams&) {}

	template <typename Name, typename Value, typename... Rest>
	static void AppendPairs(MessageParams& params, Name&& name, Value&& value, Rest&&... rest)
	{
		params.emplace_back(ToUtf16(std::forward<Name>(name)), ToUtf16(std::forward<Value>(value)));
		AppendPairs(params, std::forward<Rest>(rest)...);
	}

public:
	MessageRegistrator();

	void setDebugMode(bool dstate);
	bool getDebugMode();

	virtual void AddMessageCore(const Utf16String& description, const MessageState mstate, const MessageParams* param = nullptr) = 0;
	virtual void StatusCore(const Utf16String& message) = 0;

	static Utf16String WStringToUtf16(std::wstring_view value);
	static Utf16String WCharPtrToUtf16(const wchar_t* value);
	static Utf16String StringToUtf16(std::string_view value);

	template <typename T>
	static Utf16String ToUtf16(const T& value)
	{
		using ValueType = std::decay_t<T>;

		if constexpr (std::is_same_v<ValueType, Utf16String>)
		{
			return value;
		}
		else if constexpr (std::is_same_v<ValueType, std::wstring>)
		{
			return WStringToUtf16(value);
		}
		else if constexpr (std::is_same_v<ValueType, std::wstring_view>)
		{
			return WStringToUtf16(value);
		}
		else if constexpr (std::is_same_v<ValueType, wchar_t*> || std::is_same_v<ValueType, const wchar_t*>)
		{
			return WCharPtrToUtf16(value);
		}
		else if constexpr (std::is_same_v<ValueType, char*> || std::is_same_v<ValueType, const char*>)
		{
			return value ? StringToUtf16(value) : Utf16String();
		}
		else if constexpr (std::is_same_v<ValueType, std::string>)
		{
			return StringToUtf16(value);
		}
		else if constexpr (std::is_same_v<ValueType, std::string_view>)
		{
			return StringToUtf16(value);
		}
		else if constexpr (std::is_arithmetic_v<ValueType>)
		{
			return WStringToUtf16(std::to_wstring(value));
		}
		else if constexpr (HasCStr<ValueType>::value)
		{
			return WCharPtrToUtf16(value.c_str());
		}
		else
		{
			return WCharPtrToUtf16(static_cast<const wchar_t*>(value));
		}
	}

	void AddMessage(const Utf16String& description, const MessageState mstate, const MessageParams* param = nullptr);
	void AddMessage(std::wstring_view description, const MessageState mstate, const MessageParams* param = nullptr);
	void AddMessage(const wchar_t* description, const MessageState mstate, const MessageParams* param = nullptr);
	void AddMessage(const char* description, const MessageState mstate, const MessageParams* param = nullptr);

	void Status(const Utf16String& message);
	void Status(std::wstring_view message);
	void Status(const wchar_t* message);
	void Status(const char* message);

	template <typename Desc, typename... Args>
	void AddError(const Desc& description, Args&&... args)
	{
		static_assert((sizeof...(args) % 2) == 0, "AddError expects name/value pairs.");

		if constexpr (sizeof...(args) == 0)
		{
			AddMessage(description, msError);
		}
		else
		{
			MessageParams params;
			params.reserve(sizeof...(args) / 2);
			AppendPairs(params, std::forward<Args>(args)...);
			AddMessage(description, msError, &params);
		}
	}

	template <typename Desc, typename... Args>
	void AddMessage_(const Desc& description, const MessageState mstate, Args&&... args)
	{
		static_assert((sizeof...(args) % 2) == 0, "AddMessage_ expects name/value pairs.");
		static_assert(sizeof...(args) > 0, "AddMessage_ requires at least one name/value pair.");

		MessageParams params;
		params.reserve(sizeof...(args) / 2);
		AppendPairs(params, std::forward<Args>(args)...);
		AddMessage(description, mstate, &params);
	}

	template <typename Desc, typename... Args>
	void AddDebugMessage(const Desc& description, const MessageState mstate, Args&&... args)
	{
		if (!DebugMessage)
		{
			return;
		}

		if constexpr (sizeof...(args) == 0)
		{
			AddMessage(description, mstate);
		}
		else
		{
			AddMessage_(description, mstate, std::forward<Args>(args)...);
		}
	}
};

//---------------------------------------------------------------------------

#endif

