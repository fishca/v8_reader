//---------------------------------------------------------------------------

#include "MessageRegistration.h"

//---------------------------------------------------------------------------
MessageRegistrator::MessageRegistrator()
	: DebugMessage(false)
{
}

//---------------------------------------------------------------------------
MessageRegistrator::Utf16String MessageRegistrator::WStringToUtf16(std::wstring_view value)
{
	Utf16String result;
	result.reserve(value.size());
	for (wchar_t ch : value)
	{
		result.push_back(static_cast<char16_t>(ch));
	}
	return result;
}

//---------------------------------------------------------------------------
MessageRegistrator::Utf16String MessageRegistrator::WCharPtrToUtf16(const wchar_t* value)
{
	if (value == nullptr)
	{
		return Utf16String();
	}
	return WStringToUtf16(std::wstring_view(value));
}

//---------------------------------------------------------------------------
MessageRegistrator::Utf16String MessageRegistrator::StringToUtf16(std::string_view value)
{
	Utf16String result;
	result.reserve(value.size());
	for (unsigned char ch : value)
	{
		result.push_back(static_cast<char16_t>(ch));
	}
	return result;
}

//---------------------------------------------------------------------------
void MessageRegistrator::setDebugMode(bool dstate)
{
	DebugMessage = dstate;
}

//---------------------------------------------------------------------------
bool MessageRegistrator::getDebugMode()
{
	return DebugMessage;
}

//---------------------------------------------------------------------------
void MessageRegistrator::AddMessage(const Utf16String& description, const MessageState mstate, const MessageParams* param)
{
	AddMessageCore(description, mstate, param);
}

//---------------------------------------------------------------------------
void MessageRegistrator::AddMessage(std::wstring_view description, const MessageState mstate, const MessageParams* param)
{
	const Utf16String text = WStringToUtf16(description);
	AddMessageCore(text, mstate, param);
}

//---------------------------------------------------------------------------
void MessageRegistrator::AddMessage(const wchar_t* description, const MessageState mstate, const MessageParams* param)
{
	const Utf16String text = WCharPtrToUtf16(description);
	AddMessageCore(text, mstate, param);
}

//---------------------------------------------------------------------------
void MessageRegistrator::AddMessage(const char* description, const MessageState mstate, const MessageParams* param)
{
	const Utf16String text = description ? StringToUtf16(description) : Utf16String();
	AddMessageCore(text, mstate, param);
}

//---------------------------------------------------------------------------
void MessageRegistrator::Status(const Utf16String& message)
{
	StatusCore(message);
}

//---------------------------------------------------------------------------
void MessageRegistrator::Status(std::wstring_view message)
{
	const Utf16String text = WStringToUtf16(message);
	StatusCore(text);
}

//---------------------------------------------------------------------------
void MessageRegistrator::Status(const wchar_t* message)
{
	const Utf16String text = WCharPtrToUtf16(message);
	StatusCore(text);
}

//---------------------------------------------------------------------------
void MessageRegistrator::Status(const char* message)
{
	const Utf16String text = message ? StringToUtf16(message) : Utf16String();
	StatusCore(text);
}

