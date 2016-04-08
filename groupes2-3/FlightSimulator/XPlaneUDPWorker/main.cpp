#include "xplaneio.h"
#include <QApplication>

int main(int argc, char *argv[] )
{
	QApplication a(argc, argv) ;
    XplaneIO w ;
	w.show() ;

	return a.exec() ;
}
