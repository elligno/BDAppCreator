#include <iostream>
#include <QApplication>

namespace testpdf 
{ 
	int testmain(); 
	int testExtractPdf(int argc, char* argv[]);
	void testReadPdf();
}

int main(int argc, char *argv[])
{
//	testpdf::testReadPdf();
	std::cout << "We are about to read a pdf file to extract plain text\n";
	//testpdf::testmain();
	testpdf::testExtractPdf(argc, argv);
	std::cout << "Just finished to extract plain text from pdf file\n";
	QApplication a(argc, argv);
	return a.exec();
}
