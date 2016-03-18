/*  ---------------------------------------------------------------------------
 *  filename    :   qamtachymeter.cpp
 *  description :   IMPLEMENTATION de la classe QamTachymeter
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

#include "qamtachymeter.h"
#include <QtMath>

QamTachymeter::QamTachymeter(QWidget* parent ) : QamFlightInstrument(parent)
{
	m_class = "QamTachymeter" ;
	
	setLabel(QString("TURBINE"), TURBINE ) ;
	setUnit(QString("x 1000"), TURBINE ) ;
	setMinMax(0, 40000, TURBINE ) ;
	setThresholds(32000, 35000, TURBINE ) ;
	setValue(0, TURBINE ) ;

	m_radius[TURBINE] = QFI_RADIUS ;
	m_start[TURBINE]  = 120 ;
	m_span[TURBINE]   = 300 ;
	m_min[TURBINE]    =   0 ;
	m_max[TURBINE]    =  40 ;
	m_step[TURBINE]   = m_span[TURBINE] / ( m_max[TURBINE] - m_min[TURBINE] ) ;

	setLabel(QString("ROTOR"), ROTOR ) ;	
	setUnit(QString("t/mn x 100"), ROTOR ) ;
	setMinMax(0, 450, ROTOR ) ;
	setThresholds(280, 420, ROTOR ) ;
	setValue(0, ROTOR ) ;
	
	m_radius[ROTOR] = 0.6 * QFI_RADIUS ;
	m_start[ROTOR]  = 120 ;
	m_span[ROTOR]   = 320 ;
	m_min[ROTOR]    =   0 ;
	m_max[ROTOR]    =  45 ;
	m_step[ROTOR]   = m_span[ROTOR] / ( m_max[ROTOR] - m_min[ROTOR] ) ;

	//	animation des aiguilles (pour tests)
	
	setAdjustable(100, 0, TURBINE ) ;
//	connect(this, SIGNAL( selectChanged() ), this, SLOT( selectChanged() ) ) ;
}

// interception clic sur BP coin inférieur droit

void QamTachymeter::selectPressed(int num, bool longClic )
{
	Q_UNUSED( num ) ;
	Q_UNUSED( longClic ) ;
	
	setValue( value(ROTOR) + 10, ROTOR ) ;
}

void QamTachymeter::adjustmentChanged(int num, float value )
{
	setValue( value, num ) ;
}

void QamTachymeter::drawBackground(QPainter& painter )
{
	float w, h ;		// épaisseur et longueur du trait de graduation

	QColor	black1(15,13,11) ;
	QColor	black2(34,32,27) ;	
	QColor	white(210,200,190) ;
	QColor	red(221,65,57) ;
	QColor	yellow(205,185,83) ;
	QColor	green(101,149,112) ;

	QFont	fo1("Arial", 60 ) ;
	QFont	fo2("Arial", 50 ) ;

	// fond
	
	qfiBackground(painter, m_radius[ROTOR]+ 50, 10 ) ;

	// graduations "Turbine"

	painter.save() ;

	painter.rotate( m_start[TURBINE] ) ;
	
	for ( int i = 0 ; i <= ( m_max[TURBINE] - m_min[TURBINE] ) ; ++i ) {

		if ( i % 10 == 0 ) {		w = 20 ; h = 70 ; }
		else if ( i % 5 == 0 ) {	w = 10 ; h = 60 ; }
		else {						w =  4 ; h = 40 ; }

		qfiMarker(painter, white, m_radius[TURBINE] - 10, QSize( w, h ) ) ;
		
		painter.rotate( m_step[TURBINE] ) ;
	}
	painter.restore() ;
	
	// sérigraphie "Turbine"

	for ( int i = 0 ; i <= ( m_max[TURBINE] - m_min[TURBINE] ) ; i += 10 ) {
		float alpha = qDegreesToRadians( m_start[TURBINE] + i * m_step[TURBINE] ) ;
		float r = m_radius[TURBINE] - 120 ;
		qfiText(painter, fo1, white, QPoint( r * qCos(alpha), r * qSin(alpha) ), QString("%1").arg(i) ) ;
	}
	qfiText(painter, fo1, white, QPoint( 0, 0.8 * m_radius[TURBINE] ), label(TURBINE) ) ;
	qfiText(painter, fo2, white, QPoint( 0, 0.9 * m_radius[TURBINE] ), unit(TURBINE) ) ;

	// seuils "Turbine"	
	
	w = 20 ; h = 90 ;
	
	painter.save() ;
	painter.rotate(m_start[TURBINE] + m_step[TURBINE] * lowThreshold(TURBINE) / 1000 ) ;
	qfiMarker(painter, red, m_radius[TURBINE] - 10, QSize(w, h ) ) ;
	painter.restore() ;
	
	painter.save() ;
	painter.rotate(m_start[TURBINE] + m_step[TURBINE] * highThreshold(TURBINE) / 1000 ) ;
	qfiMarker(painter, red, m_radius[TURBINE] - 10, QSize(w, h ) ) ;
	painter.restore() ;

	// zones colorées "Turbine"

	float radius = m_radius[TURBINE] - 80 ; 
	
	float start = m_start[TURBINE] + m_step[TURBINE] * lowThreshold(TURBINE) / 100 + 4 ;
	float span = m_step[TURBINE] * ( ( ( highThreshold(TURBINE) - lowThreshold(TURBINE) ) / 1000 ) / 3 - 0.75 ) ;	
	qfiArc(painter, yellow, radius, start, span, 24 ) ;

	start += span + 4 ;
	span = m_step[TURBINE] * ( ( ( highThreshold(TURBINE) - lowThreshold(TURBINE) ) / 1000 ) / 3 - 0.5 ) ;
	qfiArc(painter, green, radius, start, span, 24 ) ;

	start += span + 4 ;
	span = m_step[TURBINE] * ( ( ( highThreshold(TURBINE) - lowThreshold(TURBINE) ) / 1000 ) / 3 - 0.8 ) ;
	qfiArc(painter, yellow, radius, start, span, 24 ) ;

	// graduations "Rotor"

	painter.save() ;
	
	radius = m_radius[ROTOR] ;
	qfiArc(painter, white, radius, m_start[ROTOR], m_span[ROTOR], 5 ) ;

	QPen pen( white ) ;
	pen.setWidth(1) ;
	painter.setPen( pen ) ;
	painter.setBrush( white ) ;

	painter.rotate( m_start[ROTOR] ) ;
	
	for ( int i = 0 ; i <= ( m_max[ROTOR] - m_min[ROTOR] ) ; ++i ) {

		if ( i % 5 == 0 ) {	w = 10 ; h = 60 ; }
		else {				w =  6 ; h = 40 ; }

		qfiMarker(painter, white, m_radius[ROTOR], QSize(w, h ) ) ;
		
		painter.rotate( m_step[ROTOR] ) ;
	}
	
	painter.restore() ;

	// sérigraphie "Rotor"
		
	for ( int i = 0 ; i <= ( m_max[ROTOR] - m_min[ROTOR] ) ; i += 10 ) {
		float alpha = qDegreesToRadians( m_start[ROTOR] + i * m_step[ROTOR] ) ;
		float r = m_radius[ROTOR] - 90 ;
		qfiText(painter, fo2, white, QPoint( r * qCos(alpha), r * qSin(alpha) ), QString("%1").arg(i/10) ) ;
	}
	qfiText(painter, fo1, white, QPoint( 0,  m_radius[ROTOR] / 4 ), label(ROTOR) ) ;
	qfiText(painter, fo2, white, QPoint( 0, -m_radius[ROTOR] / 4 ), unit(ROTOR) ) ;
	
	// seuils "Rotor"
	
	w = 20 ; h = 100 ;
	
	painter.save() ;
	painter.rotate(m_start[ROTOR] + m_step[ROTOR] * lowThreshold(ROTOR) / 10 ) ;
	qfiMarker(painter, red, m_radius[ROTOR] + 40, QSize(w, h ) ) ;
	painter.restore() ;
	
	painter.save() ;
	painter.rotate(m_start[ROTOR] + m_step[ROTOR] * highThreshold(ROTOR) / 10 ) ;
	qfiMarker(painter, red, m_radius[ROTOR] + 40, QSize(w, h ) ) ;
	painter.restore() ;

	// zones colorées "Rotor"

	radius = m_radius[ROTOR] + 25 ; 
	
	start = m_start[ROTOR] + m_step[ROTOR] * lowThreshold(ROTOR) / 10 + 5 ;
	span = m_step[ROTOR] * 3.5 ;
	qfiArc(painter, yellow, radius, start, span, 24 ) ;

	start += span + 5 ;
	span = m_step[ROTOR] * ( ( highThreshold(ROTOR) - lowThreshold(ROTOR) ) / 10 - 5.5 ) ;
	qfiArc(painter, green, radius, start, span, 24 ) ;
}

void QamTachymeter::drawForeground(QPainter& painter )
{
	float len ;						// longueur de l'aiguille orientée 0X+
	QVector<QPointF> pts ;			// points de construction dans demi-plan 0Y+
	QColor white(230,230,230) ;		// couleur de la pointe

	// aiguille "Rotor"

	len = 0.95 * m_radius[ROTOR] ;
	pts.clear() ;
	pts << QPointF( 0, 15 ) << QPointF( len - 60, 15 ) << QPointF( len, 0 ) ;
	
	painter.save() ;
	painter.rotate(m_start[ROTOR] + m_step[ROTOR] * ( value(ROTOR) / 10 ) ) ;
	qfiNeedle(painter, white, pts, 30, 0, 0.4 * len ) ;
	painter.restore() ;
	
	// aiguille "Turbine" (transparente)

	len = 0.8 * m_radius[TURBINE] ;
	pts.clear() ;
	pts << QPointF( -0.4 * m_radius[TURBINE], 20 ) << QPointF( len - 80, 20 ) << QPointF( len, 0 ) ;
	
	painter.save() ;
	painter.rotate(m_start[TURBINE] + m_step[TURBINE] * ( value(TURBINE) / 1000 ) ) ;
	qfiNeedle(painter, QColor(200, 200, 200, 120 ), pts, 40, 80 ) ;
	painter.restore() ;
	
	// axe central

	qfiAxis(painter, 30 ) ;
}

