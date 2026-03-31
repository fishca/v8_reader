//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonModules.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TCommonModules::TCommonModules() : BaseMetadataObject()
{
	root_data.reset();
	text = L"";
	textLoaded = false;
}

__fastcall TCommonModules::TCommonModules(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
	root_data.reset();
	text = L"";
	textLoaded = false;
}

__fastcall TCommonModules::TCommonModules(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
	root_data.reset();
	text = L"";
	textLoaded = false;
	name = _name;
}

void __fastcall TCommonModules::LoadTextIfNeeded()
{
	if (textLoaded)
		return;

	TBytesStream* sb = nullptr;
	TEncoding *enc = nullptr;
	TBytes bytes, sb_bytes;
	int off = 0;
	text = L"";

	if ((parent) && (!guid.IsEmpty()))
	{
		v8file* data_module = parent->GetFile(guid+".0");
		if (data_module)
		{
			v8catalog* data_module_cat = new v8catalog(data_module);
			if (data_module_cat)
			{
				auto text_module = data_module_cat->GetFile("text");
				auto image_module = data_module_cat->GetFile("image");
				if (text_module)
				{
					data_module_cat->ClearIs8316();

					sb = new TBytesStream(bytes);
					text_module->SaveToStream(sb);
					enc = nullptr;
					sb_bytes = sb->Bytes;
					if (!sb_bytes.empty())
					{
						off = TEncoding::GetBufferEncoding(sb_bytes, enc);
						if(off == 0)
						{
							delete sb;
							sb = nullptr;
						}

						if (sb)
						{
							bytes = TEncoding::Convert(enc, TEncoding::Unicode, sb_bytes, off, sb->Size-off);
							if (!bytes.empty())
							{
								String text_data = String((wchar_t*)&bytes[0], bytes.Length / 2);
								text = text_data;
							}
							else
							{
								String text_data = "";
								text = text_data;
							}
						}
						else
						{
							String text_data = "";
							text = text_data;
						}
					}
					else
					{
						text = "";
					}
					delete sb;
					sb = nullptr;
				}
				else if (image_module)
				{
					text = "Исходный текст модуля отсутствует";
				}
				else
				{
					try
					{
//						data_module->Open();
//						TBytesStream* sb = new TBytesStream(bytes);
//						data_module->SaveToStream(sb);
//						enc = NULL;
//						off = TEncoding::GetBufferEncoding(sb->Bytes, enc);
//						if(off == 0)
//						{
//							delete sb;
//						}
//
//						bytes = TEncoding::Convert(enc, TEncoding::Unicode, sb->Bytes, off, sb->Size-off);
//						String text_data = String((wchar_t*)&bytes[0], bytes.Length / 2);
//
//						text = text_data;

						text = "Не удалось получить текст модуля";
					} catch (...)
					{
					}
				}
			}
		}
	}

	textLoaded = true;
}

__fastcall TCommonModules::~TCommonModules()
{

}

String __fastcall TCommonModules::GetText()
{
	LoadTextIfNeeded();
	return text;
}

void __fastcall TCommonModules::SetText(String _text)
{
	text = _text;
}

void __fastcall TCommonModules::initializeFromTree()
{

}
