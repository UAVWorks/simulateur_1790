/*  ---------------------------------------------------------------------------
 *  filename    :   QHA.cpp
 *  description :   IMPLEMENTATION de la classe QHA
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

#include "QHA.h"
#include <QtMath>

QHA::QHA(QWidget* parent )
	: QamFlightInstrument(parent)
	, m_elapsedTimeState( STOP )
	, m_sec( 0 )
	, m_autoTime( true )
{
	setMinMax(0, 23, HOUR ) ;
    setMinMax(0, 59, MINUTE ) ;
	setMinMax(0, 59, ELAPSEDMIN ) ;
	setMinMax(0, 59, ELAPSEDSEC ) ;
	
	setValue(0, ELAPSEDMIN ) ;
	setValue(0, ELAPSEDSEC ) ;
	
    m_radius[HOUR]   = 0.83 * QFI_RADIUS ;
    m_radius[MINUTE] = QFI_RADIUS ;

	timeout() ;	// mise à l'heure initiale

	m_timer = new QTimer(this) ;
	connect(m_timer, SIGNAL(timeout()), this, SLOT(timeout()) ) ;

	m_timer->start(1000) ;	// période 1 seconde

	// BP --> 3-function operating knob (start-stop-reset)
	connect(this, SIGNAL( selectChanged() ), this, SLOT( selectChanged() ) ) ;
}

// mode HH:MM courante ou commandée par client

void QHA::setAutoTime(bool autoTime )
{
	m_autoTime = autoTime ;
	if ( !autoTime )	m_sec = 0 ;
}

bool QHA::isAutoTime() const
{
	return m_autoTime ;
}

// horloge période 1 seconde

void QHA::timeout()
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

// slot d'interception du sélecteur (bouton-poussoir)

void QHA::selectChanged()
{
	switch ( m_elapsedTimeState ) {
		case STOP :		m_elapsedTimeState = RESET ;
						setValue(0, ELAPSEDMIN ) ;
						setValue(0, ELAPSEDSEC ) ;
						break ;
		case RESET :	m_elapsedTimeState = START ;
						break ;
		default :		m_elapsedTimeState = STOP ;
						break ;
	}
}

void QHA::drawBackground(QPainter& painter )
{
    QColor	black1(230,230,230) ;
    QColor	black2(160,160,160) ;
    QColor	white(250,250,250) ; //couleur triangle

    QFont	fo1("Arial", 100 ) ;
    QFont	fo2("Arial", 50 ) ;
	
	// fond


    qfiBackground(painter, m_radius[HOUR], 100 ) ;

        QConicalGradient cg(QPointF(0.0, 0.0), 360 ) ;
        cg.setColorAt(0.0, Qt::white ) ;
        cg.setColorAt(1.0, QColor (139,69,19) ) ;
        painter.setPen(QPen(Qt::white, 8));
        painter.drawLine(-352, 0, 352, 0);
        painter.drawLine(-45, -200, 45, -200); //1 ligne (P)
        painter.drawLine(-45, -120, 45, -120); //2 ligne (P)


        float w = 0;
        float h = 30;
        float r = 0.72*QFI_RADIUS;
        float hbis = h + 3 ;
        QPolygon    triangle;

    triangle << QPoint ( r, 0) << QPoint (r + 1.5 * hbis, - 0.75 * hbis) << QPoint(r + 1.5 * hbis, 0.75* hbis) ;

painter.save();
painter.setBrush(white);
painter.rotate(-90);

        for ( int i = 0 ; i < 360 ; ++i) {
if (i == 0) painter.drawConvexPolygon(triangle);
else if (i == 45)painter.drawConvexPolygon(triangle);
else if (i == 45)painter.drawConvexPolygon(triangle);
else if (i == 315)painter.drawConvexPolygon(triangle);
else if (i == 0)painter.drawConvexPolygon(triangle);
   else if (i % 5 == 0)   painter.drawRect(r, -hbis / 0, hbis, hbis );
    else if (i % 5 == 0 )   painter.drawEllipse(r, -hbis /0, hbis, hbis);
    else                      qfiMarker(painter, white, r + h, QSize(w, h) ) ;
    painter.rotate(1.0) ;
        }
        painter.restore();

        //traingle 2







    //   triangle.setPoints(3,
      //                   -0.05*QFI_RADIUS, -0.82*QFI_RADIUS,
        //                 0, 0,
//                          0, 0);
        //painter.drawLine(-0.05*QFI_RADIUS, -0.82*QFI_RADIUS, 0.05*QFI_RADIUS, -0.82*QFI_RADIUS);  // 1 et 2
        //painter.drawLine(0.05*QFI_RADIUS, -0.82*QFI_RADIUS, 0*QFI_RADIUS, -0.71*QFI_RADIUS);  // 2 et 3
        //painter.drawLine(0*QFI_RADIUS, -0.71*QFI_RADIUS, -0.05*QFI_RADIUS, -0.82*QFI_RADIUS);  // 3 et 1

    // painter.drawPolygon(triangle);

    // graduations
        painter.save() ;
        painter.rotate(180.0) ;
        QPen pen( Qt::white ) ;
        pen.setWidth(5) ;
        painter.setPen( pen ) ;
        for ( int i = 0 ; i < 31 ; ++i ) {
            int len = ( (i % 5) == 0 ? 90: 0 ) ;
            painter.drawLine(0.82 * QFI_RADIUS - len, 0,0.82 * QFI_RADIUS - 5, 0 );
            painter.rotate(6.0) ;
        }
        painter.restore() ;
    }

   // void QChronograph::drawForeground(QPainter& painter )
   // {
     //   QPen pen ;




	// sérigraphie "heures"
/*
	for ( int i = 1 ; i <= 12 ; ++i ) {			// valeurs 1 à 12
        if ( i ==0) painter.drawConvexPolygon(triangle);
		float alpha = qDegreesToRadians( -90.0 + i * 30.0 ) ;
		float r = m_radius[HOUR] - 70 ;
		qfiText(painter, fo1, white, QPoint( r * qCos(alpha), r * qSin(alpha) ), QString("%1").arg( i ) ) ;
    }*/

    // sérigraphie "minutes"
/*
	r = m_radius[MINUTE] - 40 ;
	
	for ( int i = 15 ; i <= 60 ; i += 15 ) {	// valeurs 15, 30, 45, 60
          if ( i ==60) painter.drawConvexPolygon(triangle);
		float alpha = qDegreesToRadians( -90.0 + i * 6.0 ) ;
		qfiText(painter, fo2, white, QPoint( r * qCos(alpha), r * qSin(alpha) ), QString("%1 ").arg( i ) ) ;

    }*/
/*
	painter.save() ;
	for ( int i = 5 ; i <= 60 ; i += 5 ) {		// valeurs  5, 10, 50, 55

        painter.rotate( 30 ) ;
              if ( i ==0) painter.drawConvexPolygon(triangle);
        if ( i % 15 == 0 ) continue ;
		if (( i > 15 )&&( i < 45 ))	continue ;
		qfiText(painter, fo2, white, QPoint( 0, -r ), QString("%1 ").arg( i ) ) ;
	}	
    painter.restore() ;*/
/*
	painter.save() ;
	painter.rotate( 180 ) ;
	for ( int i = 5 ; i <= 60 ; i += 5 ) {		// valeurs 20, 25, 35, 40
		painter.rotate( 30 ) ;
		if ( i % 15 == 0 ) continue ;
		if (( i < 15 )||( i > 45 ))	continue ;
		qfiText(painter, fo2, white, QPoint( 0, r ), QString("%1 ").arg( i ) ) ;
	}	
	painter.restore() ;
*/
	// sérigraphie "swiss made"
	
/*	QFont	fo3("Arial", 20 ) ;
	
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
	QImage logo("./images/logo_thommen.png") ;
	painter.drawImage(target, logo, source ) ;
    */
//}

void QHA::drawForeground(QPainter& painter )
{
    //float len ;						// longueur de l'aiguille orientée 0X+
    //QVector<QPointF> pts ;			// points de construction dans demi-plan 0Y+
    //QColor white(230,230,230) ;		// couleur de la pointe

/*	// aiguille "Hour"

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
*/
	// axe central

   // qfiAxis(painter, 20 ) ;

	// affichage digital (CSG hors instrument)
/*
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
    */
}

