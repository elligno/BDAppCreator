
namespace testpdf 
{
	void testReadPdf() 
	{
#if 0
		PoDoFo::PdfMemDocument pdf("inputpdftest.pdf");
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
								std::string str = a[i].GetString().GetStringUtf8();
								std::cout << str << " ";
							}
						}
					}
				}
			}
		}

#endif
		//return 0;
	}
} // End of mnamespace