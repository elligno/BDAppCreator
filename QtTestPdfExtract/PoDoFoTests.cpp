#include <iostream>
#include <string>
#include <podofo.h>
#include <cstdio>
#include <QString>
#include <locale>
#include <codecvt>

using namespace PoDoFo;
namespace testpdf 
{
// 	namespace UtfConverter
// 	{
// 		std::wstring FromUtf8(const std::string& utf8string)
// 		{
// 			size_t widesize = utf8string.length();
// 			if (sizeof(wchar_t) == 2)
// 			{
// 				std::wstring resultstring;
// 				resultstring.resize(widesize + 1, L'\0');
// 				const UTF8* sourcestart = reinterpret_cast<const UTF8*>(utf8string.c_str());
// 				const UTF8* sourceend = sourcestart + widesize;
// 				UTF16* targetstart = reinterpret_cast<UTF16*>(&resultstring[0]);
// 				UTF16* targetend = targetstart + widesize;
// 				ConversionResult res = ConvertUTF8toUTF16
// 				(&sourcestart, sourceend, &targetstart, targetend, strictConversion);
// 				if (res != conversionOK)
// 				{
// 					throw std::exception("La falla!");
// 				}
// 				*targetstart = 0;
// 				return resultstring;
// 			}
// 			else if (sizeof(wchar_t) == 4)
// 			{
// 				std::wstring resultstring;
// 				resultstring.resize(widesize + 1, L'\0');
// 				const UTF8* sourcestart = reinterpret_cast<const UTF8*>(utf8string.c_str());
// 				const UTF8* sourceend = sourcestart + widesize;
// 				UTF32* targetstart = reinterpret_cast<UTF32*>(&resultstring[0]);
// 				UTF32* targetend = targetstart + widesize;
// 				ConversionResult res = ConvertUTF8toUTF32
// 				(&sourcestart, sourceend, &targetstart, targetend, strictConversion);
// 				if (res != conversionOK)
// 				{
// 					throw std::exception("La falla!");
// 				}
// 				*targetstart = 0;
// 				return resultstring;
// 			}
// 			else
// 			{
// 				throw std::exception("La falla!");
// 			}
// 			return L"";
// 		}
	void testReadPdf() 
	{
		PoDoFo::PdfMemDocument pdf("Suivicamionjour.pdf");
		for (int pn = 0; pn < pdf.GetPageCount(); ++pn)
		{
			std::cout << "Page: " << pn << std::endl;
			PoDoFo::PdfPage* page = pdf.GetPage(pn);
			PoDoFo::PdfContentsTokenizer tok(page);
			const char* token = NULL;
			PoDoFo::PdfVariant var;
			PoDoFo::EPdfContentsType type;
			while (tok.ReadNext(type, token, var))
			{
				if (type == PoDoFo::ePdfContentsType_Keyword)
				{
					// process type, token & var
					if (var.IsArray())
					{
						PoDoFo::PdfArray& a = var.GetArray();
						for (size_t i = 0; i < a.GetSize(); i++)
						{
							if (a[i].IsString())
							{
								std::string utf8 = a[i].GetString().GetStringUtf8();

								// the UTF-8 / UTF-16 standard conversion facet
// #if (!_DLL) && (_MSC_VER >= 1900 /* VS 2015*/) && (_MSC_VER <= 1911 /* VS 2017 */)
// 								std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> utf16conv;
// #endif
// 								std::u16string utf16 = utf16conv.from_bytes(utf8);
// 								std::cout << "UTF16 conversion produced " << utf16.size() << " code units:\n";
// 								for (char16_t c : utf16)
// 									std::cout << std::hex << std::showbase << c << '\n';
								
								QString w_checkStr = QString::fromUtf8(a[i].GetString().GetStringUtf8().c_str());
								QByteArray w_byteArray(a[i].GetString().GetStringUtf8().c_str());
								QString w_test = QString::fromUtf8(w_byteArray.data());
								std::cout << w_byteArray.data() << std::endl;
								std::cout << utf8 << " ";
							}
						}
					}
				}
			}
		}
		//return 0;
	}
} // End of mnamespace