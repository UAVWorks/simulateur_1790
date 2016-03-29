#ifndef TCPWORKER_H
#define TCPWORKER_H

#include "qammodbusmap.h"
#include "qamtcpclient.h"

class TCPWorker : public QamModbusMap
{
    Q_OBJECT

public :

    explicit TCPWorker(QObject * parent = 0) ;
    QamModbusMap* addSlave(const QString& conf) ;

    void setRemoteValue(const QString& name, float value ) ;
    float remoteValue (const QString& name) ;

public slots:

    void slaveCommand(int slaveIndex, int cmd) ;

private :

    void connectToSlave(int slaveIndex) ;
    QStringList slaveFullList(int slaveIndex, QamModbusMap::PrimaryTable table) ;
    QList<QamModbusMap *>       m_modbusMap ;
    QList<QamTcpClient *>       m_tcpClient ;

signals :

    void connectChanged(int slaveIndex, bool connected ) ;
    void modbusInfo(QString, QString) ;
};

#endif
