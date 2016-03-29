#include "test.h"
using namespace std ;


test::test(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    this->setGeometry(0,0,1440,900) ;
    this->setStyleSheet("background-color:black ;") ;
    this->setWindowFlags(Qt::FramelessWindowHint);

    this->show() ;
}
void test::setQFI(int x, int y, int width, int height){
    QRect rect(x,y,width,height) ;
    this->setGeometry(rect);
}

void test::loadConf(QString &file){

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
                if ( parse[0] == "QFI") {
                    if (parse[2] = "QAirSpeed")
                        createAirSpeed(parse[1],parse[3],parse[4],parse[5],parse[6]);
                    if (parse[2] = "QamTachymeter")
                        createTachymeter(parse[1],parse[3],parse[4],parse[5],parse[6]);
                    if (parse[2] = "QamChronograph")
                        createChronograph(parse[1],parse[3],parse[4],parse[5],parse[6]);
                    if (parse[2] = "QamTurnCoordinator")
                        createTurnCoordinator(parse[1],parse[3],parse[4],parse[5],parse[6]);
                    if (parse[2] = "QAltimeter")
                        createAltimeter(parse[1],parse[3],parse[4],parse[5],parse[6]);
                }
            }
        }
    }
}
void test::createAirSpeed(int id, int x, int y, int widht, int height){
    QamFlightInstrument *qairspeed = new QAirSpeed() ;
    qairspeed->setQFI( x,  y,  widht,  height) ;
    qairspeed->setParent(test);
    QListQFI[id] = qairspeed ;
    qairspeed->show() ;

}

void test::createAltimeter(int id, int x, int y, int widht, int height){
    QamFlightInstrument *qaltimeter = new QAltimeter() ;
    qaltimeter->setQFI( x,  y,  widht,  height) ;
    qaltimeter->setParent(test) ;
    QListQFI[id] = qaltimeter ;
    qaltimeter->show() ;
}

void test::createChronograph(int id, int x, int y, int widht, int height){
    QamFlightInstrument *qamchronograph = new QamChronograph() ;
    qamchronograph->setQFI( x,  y,  widht,  height) ;
    qamchronograph->setParent(test) ;
    QListQFI[id] = qamchronograph ;
    qamchronograph->show() ;
}

void test::createTurnCoordinator(int id, int x, int y, int widht, int height){
    QamFlightInstrument *qamturncoordinator = new QamTurnCoordinator() ;
    qamturncoordinator->setQFI( x,  y,  widht,  height) ;
    qamturncoordinator->setParent(test) ;
    QListQFI[id] = qamturncoordinator ;
    qamturncoordinator->show();
}

void test::createTachymeter(int id, int x, int y, int widht, int height){
    QamFlightInstrument *qamtachymeter = new QamTachymeter() ;
    qamtachymeter->setQFI( x,  y,  widht,  height) ;
    qamtachymeter->setParent(test) ;
    QListQFI[id] = qtachymeter ;
    qamtachymeter->show() ;
}
