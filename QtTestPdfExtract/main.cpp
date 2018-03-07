#include <iostream>
#include <QApplication>

namespace testpdf { int testmain(); }

int main(int argc, char *argv[])
{
	std::cout << "We are about to read a pdf file to extract plain text\n";
	testpdf::testmain();
	std::cout << "Just finished to extract plain text from pdf file\n";
	QApplication a(argc, argv);

	return a.exec();
}
