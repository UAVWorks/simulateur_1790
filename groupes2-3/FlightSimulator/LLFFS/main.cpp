#include "llffs.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LLFFS w;
    w.show();

    return a.exec();
}
