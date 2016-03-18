#include "llffs.h"

LLFFS::LLFFS(QWidget *parent) :
    QMainWindow(parent)
{

    setupUi(this);
    tcpworker = new TCPWorker ;
    maindialog = new MainDialog ;

}

LLFFS::loadConf(const QString &csv)
{
    QFile file( csv ) ;

    if ( file.open( QIODevice::ReadOnly) ) {
        QByteArray fileBytes = file.readAll();
        fileBytes.replace("\r\n", "\n") ;
        fileBytes.replace("\r", "\n") ;
        QTextStream in (fileBytes) ;

        in.setCodec("UTF-8");

        QString line = in.readLine() ;
        int nline = 1 ;

        while (!line.isNull()) {
            if ( (line.isEmpty() )||( line.startsWith("#"))) {
                line = in.readLine() ;
                nline++ ;
                continue ;
            }
            QStringList parse = line.split(";") ;

            if ( parse.size() == 1) {
                if ( parse[0] == "MODIPSLAVE") {
                    tcpworker->addSlave( parse[1].trimmed()) ;
                }
            }
        }

    }
}
