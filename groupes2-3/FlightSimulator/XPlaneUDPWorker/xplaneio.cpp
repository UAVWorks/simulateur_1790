#include "xplaneio.h"
#include <QDebug>

XplaneIO::XplaneIO(QWidget *parent) : QDialog(parent)
{
    m_udpClient = new QamUdpClient( this ) ;
    connect( m_udpClient, SIGNAL(sockReceive(QByteArray)),
             this, SLOT(sockReceive(QByteArray)) ) ;
    connect( m_udpClient, SIGNAL(sockInfo(QString)),
             this, SLOT(sockInfo(QString)) ) ;

    Dataref* d = new Dataref("sim/cockpit2/gauges/indicators/altitude_ft_pilot", 2 ) ;
    m_datarefs << d ;

    m_udpClient->setAddress( QHostAddress("192.168.0.1"));
    m_udpClient->setPort(49000);

    sendRequestToXPlane() ;

//    m_udpClient->setPort(49001);
}


void XplaneIO::sendRequestToXPlane()
{
    for ( int i = 0 ; i < m_datarefs.size() ; ++i ) {
        QByteArray frame = m_datarefs.at(i)->xplaneRrefRequest() ;
        qDebug() << "send " << toHexString( frame) ;
        m_udpClient->sockWrite( frame ) ;
    }
}

void XplaneIO::sockReceive(const QByteArray& frame )
{
    qDebug() << "recv " << toHexString( frame ) ;
}

void XplaneIO::sockInfo(const QString& msg )
{
    qDebug() << msg ;
}

// frame as hex string (format HH HH HH HH ...)

QString	XplaneIO::toHexString(const QByteArray& frame, char separator )
{
    QString s ;
    for ( int i = 0 ; i < frame.count() ; ++i ) {
        s += QString("%1").arg( quint8( frame.at(i) ), 2, 16, QLatin1Char('0') ).toUpper() ;
        s += separator ;
    }
    return s ;
}
