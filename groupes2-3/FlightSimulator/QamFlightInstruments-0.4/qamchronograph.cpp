/*  ---------------------------------------------------------------------------
 *  filename    :   qamchronograph.cpp
 *  description :   IMPLEMENTATION de la classe QamChronograph
 *
 *	project     :	Widgets "Flight Instrument"
 *  start date  :   octobre 2015
 *  ---------------------------------------------------------------------------
 *  Copyright 2015-2016 by Alain Menu   <alain.menu@ac-creteil.fr>
 *
 *  This file is part of "Qam Flight Instruments Widgets Library"
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

#include "qamchronograph.h"
#include <QtMath>
//#include <QDebug>

QamChronograph::QamChronograph(QWidget* parent )
	: QamFlightInstrument(parent)
	, m_elapsedTimeState( STOP )
	, m_sec( 0 )
	, m_autoTime( true )
{
	m_class = "QamChronograph" ;
	
	setMinMax(0, 23, HOUR ) ;
	setMinMax(0, 59, MINUTE ) ;
	setMinMax(0, 59, ELAPSEDMIN ) ;
	setMinMax(0, 59, ELAPSEDSEC ) ;
	
	setValue(0, ELAPSEDMIN ) ;
	setValue(0, ELAPSEDSEC ) ;
	
	m_radius[HOUR]   = 0.77 * QFI_RADIUS ;
	m_radius[MINUTE] = QFI_RADIUS ;

	timeout() ;	// mise à l'heure initiale

	m_timer = new QTimer(this) ;
	connect(m_timer, SIGNAL(timeout()), this, SLOT(timeout()) ) ;

	m_timer->start(1000) ;	// période 1 seconde
}

// mode HH:MM courante ou commandée par client

void QamChronograph::setAutoTime(bool autoTime )
{
	m_autoTime = autoTime ;
	if ( !autoTime )	m_sec = 0 ;
}

bool QamChronograph::isAutoTime() const
{
	return m_autoTime ;
}

// horloge période 1 seconde

void QamChronograph::timeout()
{
	if ( isAutoTime() ) {
		QTime time = QTime::currentTime() ;
		setValue(time.hour(), HOUR ) ;
		setValue(time.minute(), MINUTE ) ;
		m_sec = time.second() ;
	}
	
	if ( m_elapsedTimeState == START ) {
		float sec = value(ELAPSEDSEC) ;
		if ( sec == maximum(ELAPSEDSEC) ) {
			setValue(0, ELAPSEDSEC ) ;
			float min = value(ELAPSEDMIN) ;
			setValue(min == maximum(ELAPSEDMIN) ? 0 : min + 1, ELAPSEDMIN ) ;
		}
		else {
			setValue(sec + 1, ELAPSEDSEC ) ;
		}
	}	
	update() ;
}

// spécialisation du slot d'interception du sélecteur (bouton-poussoir)
// 3-function operating knob (start-stop-reset)

void QamChronograph::selectPressed(int num, bool longClic )
{
//	qDebug() << "QamChronograph::selectPressed()" ;
	
	Q_UNUSED( num ) ;
	Q_UNUSED( longClic ) ;
	
	switch ( m_elapsedTimeState ) {
		case STOP :		m_elapsedTimeState = RESET ;
						setValue(0, ELAPSEDMIN ) ;
						setValue(0, ELAPSEDSEC ) ;
						break ;
		case RESET :	m_elapsedTimeState = START ;
//						emit alarmState( QamFlightInstrument::Off, QamFlightInstrument::On ) ;
						emit alarmState(this->id(), 1, QamFlightInstrument::On ) ;
						break ;
		default :		m_elapsedTimeState = STOP ;
//						emit alarmState( QamFlightInstrument::Off, QamFlightInstrument::Off ) ;
						emit alarmState(this->id(), 1, QamFlightInstrument::Off ) ;
						break ;
	}
}

void QamChronograph::drawBackground(QPainter& painter )
{
	QColor	black1(15,13,11) ;
	QColor	black2(34,32,27) ;	
	QColor	white(230,220,210) ;
	
	QFont	fo1("Arial", 100 ) ;
	QFont	fo2("Arial", 50 ) ;
	
	// fond
	
	qfiBackground(painter, m_radius[HOUR], 10 ) ;

	// graduations

	float w = 10 ;				// épaisseur du trait de graduation
	float h = 30 ;				// longueur du trait de graduation
	float r = m_radius[HOUR] ;	// rayon de départ
	float hbis = h + 3 ;		// correction pour marquers carrés, ronds, ...
	QPolygon	triangle ;		// triangle marquage origine

	triangle << QPoint(r, 0) << QPoint(r + 1.5 * hbis, -0.75 * hbis) << QPoint(r + 1.5 * hbis, 0.75 * hbis) ;
	
	painter.save() ;
	painter.setBrush( white ) ;
	painter.rotate( -90 ) ;
	for ( int i = 0 ; i < 60 ; ++i ) {
		if ( i == 0 ) 				painter.drawConvexPolygon( triangle ) ;
		else if ( i % 15 == 0 )		painter.drawRect(r, -hbis / 2, hbis, hbis ) ;
		else if ( i % 5 == 0 )		painter.drawEllipse(r, -hbis / 2, hbis, hbis ) ;
		else 						qfiMarker(painter, white, r + h, QSize(w, h ) ) ;
		painter.rotate( 6.0 ) ;
	}
	painter.restore() ;
		
	// sérigraphie "heures"
	
	for ( int i = 1 ; i <= 12 ; ++i ) {			// valeurs 1 à 12
		float alpha = qDegreesToRadians( -90.0 + i * 30.0 ) ;
		float r = m_radius[HOUR] - 70 ;
		qfiText(painter, fo1, white, QPoint( r * qCos(alpha), r * qSin(alpha) ), QString("%1").arg( i ) ) ;
	}
	
	// sérigraphie "minutes"
		
	r = m_radius[MINUTE] - 40 ;
	
	for ( int i = 15 ; i <= 60 ; i += 15 ) {	// valeurs 15, 30, 45, 60
		float alpha = qDegreesToRadians( -90.0 + i * 6.0 ) ;
		qfiText(painter, fo2, white, QPoint( r * qCos(alpha), r * qSin(alpha) ), QString("%1 ").arg( i ) ) ;
	}
	
	painter.save() ;
	for ( int i = 5 ; i <= 60 ; i += 5 ) {		// valeurs  5, 10, 50, 55
		painter.rotate( 30 ) ;
		if ( i % 15 == 0 ) continue ;
		if (( i > 15 )&&( i < 45 ))	continue ;
		qfiText(painter, fo2, white, QPoint( 0, -r ), QString("%1 ").arg( i ) ) ;
	}	
	painter.restore() ;

	painter.save() ;
	painter.rotate( 180 ) ;
	for ( int i = 5 ; i <= 60 ; i += 5 ) {		// valeurs 20, 25, 35, 40
		painter.rotate( 30 ) ;
		if ( i % 15 == 0 ) continue ;
		if (( i < 15 )||( i > 45 ))	continue ;
		qfiText(painter, fo2, white, QPoint( 0, r ), QString("%1 ").arg( i ) ) ;
	}	
	painter.restore() ;

	// sérigraphie "swiss made"
	
	QFont	fo3("Arial", 20 ) ;
	
	painter.save() ;
	painter.rotate(10) ;
	qfiText(painter, fo3, white, QPoint( 0, r + 10 ), QString("SWISS") ) ;
	painter.rotate(-20) ;
	qfiText(painter, fo3, white, QPoint( 0, r + 10 ), QString("MADE") ) ;
	painter.restore() ;
		
	// logo "Thommen"
	
	float wi = 621.0 ;	// image width
	float hi = 156.0 ;	// image height
	float si = 0.3 ;	// scale
	QRectF target(-0.5 * wi * si, 0.3 * m_radius[HOUR], wi * si, hi * si ) ;
	QRectF source(0.0, 0.0, wi, hi ) ;
	QImage logo(":/qfiImages/logo_thommen.png") ;
	painter.drawImage(target, logo, source ) ;
}

void QamChronograph::drawForeground(QPainter& painter )
{
	float len ;						// longueur de l'aiguille orientée 0X+
	QVector<QPointF> pts ;			// points de construction dans demi-plan 0Y+
	QColor white(230,230,230) ;		// couleur de la pointe

	// aiguille "Hour"

	len = 0.6 * m_radius[HOUR] ;
	pts.clear() ;
	pts << 	QPointF( 0, 20 ) << QPointF( len - 70, 35 ) << QPointF( len, 0 ) ;
	
	painter.save() ;
	painter.rotate( -90 + 30.0 * ( (int)value(HOUR) % 12 + value(MINUTE) / 60 ) ) ;
	qfiNeedle(painter, white, pts, 35, 0, 0.35 * len ) ;
	painter.restore() ;
	
	// aiguille "Minute"

	len = 0.95 * m_radius[HOUR] ;
	pts.clear() ;
	pts << QPointF( 0, 15 ) << QPointF( len - 100, 25 ) << QPointF( len, 0 ) ;

	painter.save() ;
	painter.rotate( -90 + 6.0 * ( (int)value(MINUTE) + m_sec / 60 ) ) ;
	qfiNeedle(painter, white, pts, 25, 0, 0.35 * len ) ;
	painter.restore() ;
	
	// aiguille "Elapsed Minute"

	len = 1.025 * m_radius[HOUR] ;
	pts.clear() ;
	pts <<  QPointF( 0, 10 ) << QPointF( len - 70, 10 ) << QPointF( len - 70, 30 ) << QPointF( len, 0 ) ;
	
	painter.save() ;
	painter.rotate( -90 + 6.0 * ( value(ELAPSEDMIN) + value(ELAPSEDSEC) / 60 ) ) ;
	qfiNeedle(painter, white, pts, 30, 0, 0.7 * len ) ;
	painter.restore() ;
	
	// aiguille "Elapsed Second"

	len = 1.05 * m_radius[HOUR] ;
	pts.clear() ;
	pts << QPointF( -0.4 * m_radius[HOUR], 10 ) << QPointF( 0.8 * len, 10 ) << QPointF( len, 5 ) ;
	
	painter.save() ;
	painter.rotate( -90 + 6.0 * value(ELAPSEDSEC) ) ;
	qfiNeedle(painter, white, pts, 30, 30, 0.2 * len ) ;
	painter.restore() ;
	
	// axe central

	qfiAxis(painter, 20 ) ;

	// affichage digital (CSG hors instrument)

	painter.save() ;
	QFont font("Arial", 40 ) ;
	QColor	color(0, 0, 0 ) ;
	QPoint	point(-QFI_RADIUS + 75,-QFI_RADIUS + 50 ) ;
	QString s = QString("%1:%2 ").arg((int)value(HOUR),2,10,QLatin1Char('0')).arg((int)value(MINUTE),2,10,QLatin1Char('0')) ;
	qfiText(painter, font, color, point, s ) ;
	point = QPoint(-QFI_RADIUS + 75,-QFI_RADIUS + 100 ) ;
	s = QString("%1:%2 ").arg((int)value(ELAPSEDMIN),2,10,QLatin1Char('0')).arg((int)value(ELAPSEDSEC),2,10,QLatin1Char('0')) ;
	qfiText(painter, font, color, point, s ) ;
	painter.restore() ;
	
}
