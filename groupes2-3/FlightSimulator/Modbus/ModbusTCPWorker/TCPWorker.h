#ifndef TCPWORKER_H
#define TCPWORKER_H

#include "qammodbusmap.h"
#include "qamtcpclient.h"

class TCPWorker : public QamModbusMap
{
    Q_OBJECT

public :
    QamModbusMap* addSlave(const QString& conf) ;
private :
    QList<QamModbusMap *>       m_modbusMap ;
    QList<QamTcpClient *>       m_tcpClient ;
};

#endif
