#include "qamudpclient.h"

QamUdpClient::QamUdpClient(QObject* parent )
	: QUdpSocket(parent)
{
    connect( this, SIGNAL( readyRead() ), this, SLOT( sockRead() ) ) ;
}

void QamUdpClient::setAddress(const QHostAddress& address )
{
	m_distAddr = address ;
}

void QamUdpClient::setPort(quint16 port )
{
	m_distPort = port ;
}

void QamUdpClient::sockRead()
{
	while ( hasPendingDatagrams() ) {
		QByteArray  datagram ;
		datagram.resize( pendingDatagramSize() ) ;
		readDatagram(datagram.data(), datagram.size(), &m_distAddr, &m_distPort ) ;
		emit sockInfo(QString("from %1:%2").arg( m_distAddr.toString() ).arg( m_distPort) ) ;
		emit sockReceive( datagram ) ;
	}
}

void QamUdpClient::sockWrite(const QByteArray& data )
{
	if ( m_distAddr.isNull() ) {
		emit sockInfo("unknown host..." ) ;
		return ;
	}
    writeDatagram( data.data(), data.size(), m_distAddr, m_distPort ) ;

	QString s = QString("local port %1 ").arg( localPort() ) ;
	s += QString("to %1:%2").arg( m_distAddr.toString() ).arg( m_distPort ) ;
	emit sockInfo( s ) ;
}
