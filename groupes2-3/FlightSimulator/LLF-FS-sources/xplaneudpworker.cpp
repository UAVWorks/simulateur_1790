/*  ---------------------------------------------------------------------------
 *  filename    :   xplaneudpworker.cpp
 *  description :   IMPLEMENTATION de la classe XPlaneUdpWorker
 *
 *	project     :	FlightSim
 *  start date  :   février 2016
 *  ---------------------------------------------------------------------------
 *  Copyright 2016 by Alain Menu   <alain.menu@ac-creteil.fr>
 *
 *  This file is part of "LLF Flight Simulator Project"
 *
 *  This program is free software ;  you can  redistribute it and/or  modify it
 *  under the terms of the  GNU General Public License as published by the Free
 *  Software Foundation ; either version 3 of the License, or  (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY ; without even the  implied  warranty  of  MERCHANTABILITY  or
 *  FITNESS FOR  A PARTICULAR PURPOSE. See the  GNU General Public License  for
 *  more details.
 *
 *	You should have  received  a copy of the  GNU General Public License  along
 *	with this program. If not, see <http://www.gnu.org/licenses/>.
 *  ---------------------------------------------------------------------------
 */

#include <QCoreApplication>
#include "xplaneudpworker.h"

#include <QThread>

//XPlaneUdpWorker::XPlaneUdpWorker(const QString& host, int port, QList<DataRef*>& datarefs )
XPlaneUdpWorker::XPlaneUdpWorker(const QString& host, int recvPort, int sendPort, QList<DataRef*>& datarefs )
	: m_udpHost( host )
//	, m_udpPort( port )
	, m_udpRecvPort( recvPort )
	, m_udpSendPort( sendPort )
	, m_datarefs( datarefs )
{
	m_udpSendSocket = new QamUdpSocket( this ) ;
	m_udpSendSocket->sockBind() ;
	m_udpSendSocket->setRemoteHost( m_udpHost, m_udpRecvPort ) ;
	
	connect( m_udpSendSocket, SIGNAL( sockInfo(const QString& ) ),
			 this,        	  SIGNAL( udpInfo(const QString& ) ) ) ;
//
	connect( m_udpSendSocket, SIGNAL( sockReceived(const QByteArray& ) ),
			 this,        	  SLOT(   received(const QByteArray& ) ) ) ;
//
	m_udpRecvSocket = new QamUdpSocket( this ) ;
//	m_udpRecvSocket->sockBind( m_udpSendPort ) ;
	m_udpRecvSocket->sockBind() ;
	m_udpRecvSocket->setRemoteHost( m_udpHost, m_udpSendPort ) ;

	connect( m_udpRecvSocket, SIGNAL( sockInfo(const QString& ) ),
			 this,        	  SIGNAL( udpInfo(const QString& ) ) ) ;

	connect( m_udpRecvSocket, SIGNAL( sockReceived(const QByteArray& ) ),
			 this,        	  SLOT(   received(const QByteArray& ) ) ) ;
/*
	m_udpSocket = new QamUdpSocket( this ) ;
	m_udpSocket->sockBind() ;
	m_udpSocket->setRemoteHost( m_udpHost, m_udpPort ) ;
	
	connect( m_udpSocket, SIGNAL( sockInfo(const QString& ) ),
			 this,        SIGNAL( udpInfo(const QString& ) ) ) ;
			 
	connect( m_udpSocket, SIGNAL( sockReceived(const QByteArray& ) ),
			 this,        SLOT(   received(const QByteArray& ) ) ) ;
*/
	m_rrefWaitingTimer = new QTimer ;			 
	connect(m_rrefWaitingTimer, SIGNAL( timeout() ), this, SLOT( timeout() ) ) ;
}

void XPlaneUdpWorker::start()
{
	setXPlaneTrafic() ;
}

void XPlaneUdpWorker::stop()
{
	setXPlaneTrafic( false ) ;
	
	if ( m_rrefWaitingTimer->isActive() )	m_rrefWaitingTimer->stop() ;
	delete m_rrefWaitingTimer ;

//    m_udpSocket->sockClose() ;
//    delete m_udpSocket ;
    m_udpSendSocket->sockClose() ;
    delete m_udpSendSocket ;
    m_udpRecvSocket->sockClose() ;
    delete m_udpRecvSocket ;
}

void XPlaneUdpWorker::timeout()
{
	m_rrefWaitingId = -1 ;
}

// émission des requêtes RREF

void XPlaneUdpWorker::setXPlaneTrafic(bool start )
{
//	QString ipAddr = m_udpSocket->address().toString() ;
	QString ipAddr = m_udpSendSocket->address().toString() ;
//	emit udpInfo( QString("using %1:%2 for X-Plane Host").arg(ipAddr).arg(m_udpPort) ) ;
	if ( start )	emit udpInfo( QString("using %1 for X-Plane Host").arg(ipAddr) ) ;

	for ( int i = 0 ; i < m_datarefs.size() ; ++i ) {
		DataRef* d = m_datarefs.at(i) ;
		
		if ( !d->isRref() )	continue ;
	
		if ( start ) {	
			emit udpInfo(QString("sending RREF request for \"%1\"").arg( d->sourceName() ) ) ; 

			m_rrefWaitingId = d->id() ;
//			m_rrefWaitingTimer->start( 1250 ) ;
			
//			m_udpSocket->sockWrite( d->xplaneRrefRequest() ) ;
//			m_udpSendSocket->sockWrite( d->xplaneRrefRequest() ) ;
			this->send( d->xplaneRrefRequest() ) ;

QThread::msleep(1000) ;
			// attendre la première trame de réponse...
//			while ( m_rrefWaitingId > 0 )	QCoreApplication::processEvents() ;
//			m_rrefWaitingTimer->stop() ;
//			if ( m_rrefWaitingId == -1 )	emit udpInfo("no answer!") ;
		}
		else {
//			m_udpSocket->sockWrite( d->xplaneRrefStop() ) ;
//			m_udpSendSocket->sockWrite( d->xplaneRrefStop() ) ;
			this->send( d->xplaneRrefStop() ) ;
		}
	}
}

// réception des RREF

void XPlaneUdpWorker::received(const QByteArray& data )
{
	QString cmd = data.left(4) ;
//qDebug() << "XPlaneUdpWorker::received()" ;
	if ( cmd == "RREF" ) {
		XPlaneRrefAnswer* p = (XPlaneRrefAnswer*)( data.data() + 5 ) ;
		
		if ( p->id == m_rrefWaitingId )	m_rrefWaitingId = 0 ;

		emit rrefReceived(p->id, p->value ) ;

        qDebug() << "recv" << p->id << p->value ;
	}
}

// émission des DREF

void XPlaneUdpWorker::send(const QByteArray& data )
{
//	m_udpSocket->sockWrite( data ) ;
//	m_udpSocket->sockWrite( data, 49000 ) ;
	m_udpSendSocket->sockWrite( data, m_udpRecvPort ) ;
}
