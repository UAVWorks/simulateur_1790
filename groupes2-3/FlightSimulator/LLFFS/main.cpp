#include "llffs.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    new llffs;
    return a.exec();
}
