#include "TCPWorker.h"

TCPWorker::TCPWorker(QObject* parent)
    : QamModbusMap(parent)
{

}

QamModbusMap * TCPWorker::addSlave(const QString &conf)
{
    QamModbusMap* map = new QamModbusMap(QamModbusMap::ClientMode, this)  ;
    QamTcpClient* client = new QamTcpClient(map, this ) ;

    connect( map, SIGNAL(info(QString,QString)),
             this, SLOT(info(QString,QString)) ) ;
    map->loadMap( fileName ) ;
    m_modbusMap << map ;
    m_tcpClient << client ;
    return map ;
}
