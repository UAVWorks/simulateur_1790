#include "TCPWorker.h"

TCPWorker::TCPWorker(QObject* parent)
    : QamModbusMap(parent)
{

}

QamModbusMap * TCPWorker::addSlave(const QString &conf)
{
       m_modbusMap << new QamModbusMap ;

}
