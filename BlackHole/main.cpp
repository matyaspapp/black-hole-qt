#include "view/blackholeview.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BlackHoleView w;
    w.show();
    return a.exec();
}
