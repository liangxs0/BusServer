#include "bus.h"
#include <QApplication>
//#include <QPixmap>
//#include <QSplashScreen>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Bus w;
    w.show();
//    Add A;
//    A.show();
    return a.exec();

}
