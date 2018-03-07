// Qt include
#include <QApplication>
// App includes
#include "testguilayout.h"
#include "TestGuiImpl.h"
#include "BasicTest.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

#if 0
    bdGui::TestGuiImpl w;
    w.show();
#else
    bdGui::TestGuiLayout w_test1;
    w_test1.show();
// 	bdGui::BasicTest w_tst;
// 	w_tst.show();
#endif

    return a.exec();
}
