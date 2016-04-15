#include "test.h"
using namespace std ;


test::test(QWidget *parent) :
    QWidget(parent),
    configFile(QString("conf.csv"))
{
    setupUi(this);
    this->setGeometry(0,0,1440,900) ;
    this->setStyleSheet("background-color:black ;") ;
    this->setWindowFlags(Qt::FramelessWindowHint);
    cout << "Config initiale"<< endl ;

    loadConf(configFile);
    this->show() ;
}


void test::setQFI(int x, int y, int width, int height, QamFlightInstrument* QFI){
    QRect rect(x,y,width,height) ;
    QFI->setGeometry(rect);
    QFI->setParent(this) ;
}

bool test::loadConf(QString &csv){

    QFile file( csv ) ;

    if ( file.open( QIODevice::ReadOnly) ) {
        cout << "Ouverture du CSV" << endl ;
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

            if ( parse.size() == 7) {
                if ( parse[0] == "QFI") {
                    if (parse[2] == "QAirSpeed")
                        createAirSpeed(parse[1].toInt(),parse[3].toInt(),parse[4].toInt(),parse[5].toInt(),parse[6].toInt());
                    if (parse[2] == "QamTachymeter")
                        createTachymeter(parse[1].toInt(),parse[3].toInt(),parse[4].toInt(),parse[5].toInt(),parse[6].toInt());
                    if (parse[2] == "QamChronograph")
                        createChronograph(parse[1].toInt(),parse[3].toInt(),parse[4].toInt(),parse[5].toInt(),parse[6].toInt());
                    if (parse[2] == "QamTurnCoordinator")
                        createTurnCoordinator(parse[1].toInt(),parse[3].toInt(),parse[4].toInt(),parse[5].toInt(),parse[6].toInt());
                    if (parse[2] == "QAltimeter")
                        createAltimeter(parse[1].toInt(),parse[3].toInt(),parse[4].toInt(),parse[5].toInt(),parse[6].toInt());
                    if (parse[2]== "QHA")
                        createQHA(parse[1].toInt(),parse[3].toInt(),parse[4].toInt(),parse[5].toInt(),parse[6].toInt());
                }
            }
            if (parse[0] == "RREF_QFI") {
                createRrefQfi(parse[1].toInt(),parse[2].toInt(),parse[3],parse[4].toInt(),parse[5].toInt(),parse[6].toInt());
            }
            line = in.readLine() ;
            nline++ ;
        }
        file.close();
        return true ;
    }
    cout << "Fichier Introuvable" << endl ;
    return false ;

}
void test::createAirSpeed(int id, int x, int y, int widht, int height){
    QamFlightInstrument *qairspeed = new QAirSpeed() ;
    setQFI( x,  y,  widht,  height, qairspeed) ;
    //qairspeed->setParent(test);
    QListQFI[id] = qairspeed ;
    qairspeed->show() ;

}

void test::createAltimeter(int id, int x, int y, int widht, int height){
    QamFlightInstrument *qaltimeter = new QAltimeter() ;
    setQFI( x,  y,  widht,  height, qaltimeter) ;
    //qaltimeter->setParent(test) ;
    QListQFI[id] = qaltimeter ;
    qaltimeter->show() ;
}

void test::createChronograph(int id, int x, int y, int widht, int height){
    QamFlightInstrument *qamchronograph = new QamChronograph() ;
    setQFI( x,  y,  widht,  height, qamchronograph) ;
    //qamchronograph->setParent(test) ;
    QListQFI[id] = qamchronograph ;
    qamchronograph->show() ;
}

void test::createTurnCoordinator(int id, int x, int y, int widht, int height){
    QamFlightInstrument *qamturncoordinator = new QamTurnCoordinator() ;
    setQFI( x,  y,  widht,  height, qamturncoordinator) ;
    //qamturncoordinator->setParent(test) ;
    QListQFI[id] = qamturncoordinator ;
    qamturncoordinator->show();
}

void test::createTachymeter(int id, int x, int y, int widht, int height){
    QamFlightInstrument *qamtachymeter = new QamTachymeter() ;
    setQFI( x,  y,  widht,  height, qamtachymeter) ;
    //qamtachymeter->setParent(test) ;
    QListQFI[id] = qamtachymeter ;
    qamtachymeter->show() ;
}

void test::createQHA(int id, int x, int y, int width, int height){
    QamFlightInstrument *qha = new QHA() ;
    setQFI( x, y, width, height, qha) ;
    QListQFI[id] = qha ;
    qha->show();
}

void test::createRrefQfi(int iId, int aId, QString &path, int freq, int scale, int offset){
    DataRef * mb = new DataRef( path)
}
