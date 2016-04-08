#ifndef QAMUDPCLIENT_H
#define QAMUDPCLIENT_H

#include <QUdpSocket>

class QamUdpClient : public QUdpSocket
{
	Q_OBJECT

  public:
	explicit QamUdpClient(QObject* parent = 0 ) ;

	void setAddress(const QHostAddress& address ) ;
	void setPort(quint16 port ) ;

  private slots :
	void sockRead() ;

  public slots :
	void sockWrite(const QByteArray& data ) ;

  signals:
	void sockReceive(const QByteArray& ) ;
	void sockInfo(const QString& ) ;

  private :

	QHostAddress    m_distAddr ;
	quint16         m_distPort ;
} ;

#endif // QAMUDPCLIENT_H
