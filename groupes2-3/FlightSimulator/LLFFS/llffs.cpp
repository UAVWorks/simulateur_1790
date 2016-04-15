#include "llffs.h"
using namespace std ;


llffs::llffs(QObject *parent) :
    QObject(parent) ,
    configFile(QString("conf.csv"))
{
    qfiDisplay = new QFIPanel() ;
    mainDialog = new MainDialog() ;

    loadConf(configFile);

    m_udpWorker = new XPlaneUdpWorker("192.168.0.1", 49000, 49001, QListDat ) ;
    connect(m_udpWorker, SIGNAL(rrefReceived(int,float)), this, SLOT(exploitRref(int,float))) ;
    m_udpWorker->start();

}


void llffs::setQFI(int x, int y, int width, int height, QamFlightInstrument* QFI, int id)
{
    QRect rect(x,y,width,height) ;
    QFI->setId(id) ;
    QFI->setGeometry(rect);
    QFI->setParent(qfiDisplay) ;
    QFI->show();
}

bool llffs::loadConf(QString &csv){

    QFile file( csv ) ;

    if ( file.open( QIODevice::ReadOnly) ) {
//      cout << "Ouverture du CSV" << endl ;
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
            for (int i = 0; i < parse.size(); i++){
                parse[i]=parse[i].trimmed() ;
            }



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
                    if ( parse[2] == "QVariometer")
                        createVariometer(parse[1].toInt(),parse[3].toInt(),parse[4].toInt(),parse[5].toInt(),parse[6].toInt()) ;
                    if ( parse[2] == "QGyro")
                        createGyroDir(parse[1].toInt(),parse[3].toInt(),parse[4].toInt(),parse[5].toInt(),parse[6].toInt()) ;
                    if (parse[2]== "QHA")
                        createQHA(parse[1].toInt(),parse[3].toInt(),parse[4].toInt(),parse[5].toInt(),parse[6].toInt());
                      qDebug() << parse[2] ;
                }

            }
            if (parse[0] == "RREF_QFI"){

                DataRef *dataref = new DataRef(parse[3],parse[4].toInt()) ;

                if (parse.size() == 5)
                    dataref->bindToInstrument(parse[1].toInt(),parse[2].toInt());

                if ( parse.size() == 7)
                    dataref->bindToInstrument(parse[1].toInt(),parse[2].toInt(),parse[5].toFloat(),parse[6].toFloat());

                qDebug() << parse[3] ;

                QListDat << dataref ;

            }
            if ( parse.size() == 2){
                if (parse[0] == "MODISPLAVE"){
                    ModbusTcpWorker * coco = new ModbusTcpWorker() ;
                    coco->addModbusSlave(parse[1]) ;
                }
            }

            line = in.readLine() ;
            nline++ ;
        }

        file.close();
        return true ;
    }
    return false ;


}
void llffs::createAirSpeed(int id, int x, int y, int widht, int height){
    QamFlightInstrument *qairspeed = new QAirSpeed() ;
    setQFI( x,  y,  widht,  height, qairspeed, id) ;
    QListQFI << qairspeed ;
    qairspeed->show() ;

}

void llffs::createAltimeter(int id, int x, int y, int widht, int height){
    QamFlightInstrument *qaltimeter = new QAltimeter() ;
    setQFI( x,  y,  widht,  height, qaltimeter, id ) ;
    QListQFI << qaltimeter ;
    qaltimeter->show() ;
}

void llffs::createChronograph(int id, int x, int y, int widht, int height){
    QamFlightInstrument *qamchronograph = new QamChronograph() ;
    dynamic_cast<QamChronograph*>(qamchronograph)->setAutoTime(false) ;
    setQFI( x,  y,  widht,  height, qamchronograph, id) ;
    QListQFI << qamchronograph ;
    qamchronograph->show() ;
}

void llffs::createTurnCoordinator(int id, int x, int y, int widht, int height){
    QamFlightInstrument *qamturncoordinator = new QamTurnCoordinator();
    setQFI( x,  y,  widht,  height, qamturncoordinator, id) ;
    QListQFI << qamturncoordinator ;
    qamturncoordinator->show();
}

void llffs::createTachymeter(int id, int x, int y, int widht, int height){
    QamFlightInstrument *qamtachymeter = new QamTachymeter() ;
    setQFI( x,  y,  widht,  height, qamtachymeter, id) ;
    QListQFI << qamtachymeter ;
    qamtachymeter->show() ;
}

void llffs::createVariometer(int id, int x, int y, int widht, int height)
{
    QamFlightInstrument * v = new QamVariometer() ;
    setQFI(x , y, widht, height, v, id) ;
    QListQFI <<  v ;
    v->show();
}

void llffs::createGyroDir(int id, int x, int y, int widht, int height)
{
    QamFlightInstrument * v = new QamGyroDir() ;
    setQFI(x, y, widht, height, v, id) ;
    QListQFI << v ;
    v->show() ;
}

void llffs::createQHA(int id, int x, int y, int width, int height){
    QamFlightInstrument *qha = new QHA() ;
    setQFI( x, y, width, height, qha, id) ;

    QListQFI << qha ;
    qha->show();
}

void llffs::exploitRref(int id, float value)
{
    for (int i = 0; i < QListDat.size(); i++)
    {
       if(QListDat[i]->id() == id)
           if(QListDat[i]->isRrefQfi())
           {
               int a = QListDat[i]->instrumentId() ;
               int b = QListDat[i]->instrumentAxis() ;
               for (int j = 0; j < QListQFI.size(); j++)
               {
                   if(QListQFI[j]->id() == a)
                   {
                       QListQFI[j]->setValue(value, b) ;
                   }
               }
        }
    }
}
