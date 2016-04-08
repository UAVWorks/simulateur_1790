#ifndef XPLANEIO_H
#define XPLANEIO_H

#include <QDialog>
#include "qamudpclient.h"
#include "Dataref.h"

class XplaneIO : public QDialog
{
    Q_OBJECT
public:
    explicit XplaneIO(QWidget *parent = 0);

    void sendRequestToXPlane() ;

signals:

  public slots:
    void sockReceive(const QByteArray& frame ) ;
    void sockInfo(const QString& msg ) ;

  private:
    QString	toHexString(const QByteArray& frame, char separator = ' ' ) ;

    QamUdpClient*	m_udpClient ;
    QList<Dataref*> m_datarefs ;
};

#endif // XPLANEIO_H
