/*  ---------------------------------------------------------------------------
 *  filename    :   qairspeed.cpp
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

#include "qairspeed.h"
#include <QtMath>
#include <QDebug>

QAirSpeed::QAirSpeed(QWidget* parent )
    : QFlightInstrument(parent)
    , m_isUnitKmh( true )
{
    setMinMax(0, 140, AIRSPEED ) ;
    //setThresholds(16+value(POTEN),111.5, AIRSPEED ) ;
    setValue(0, AIRSPEED ) ;

    //Potentiometre
    setMinMax(0, 1000, POTEN ) ;
    setValue(0, POTEN) ;

    m_radius[AIRSPEED] = QFI_RADIUS ;
    m_start[AIRSPEED]  = 120 ;
    m_span[AIRSPEED]   = 300 ;
    m_span2[AIRSPEED]  = 520;
    m_min[AIRSPEED]    =   0 ;
    m_max[AIRSPEED]    =  20 ;
    m_step[AIRSPEED]   = m_span[AIRSPEED] / ( m_max[AIRSPEED] - m_min[AIRSPEED] ) ;
    m_step2[AIRSPEED]   = m_span2[AIRSPEED] / ( m_max[AIRSPEED] - m_min[AIRSPEED] ) ;

    //	animation des aiguilles (pour tests)

    setAdjustable(1, 0, 250 ) ;
    adjustmentChanged(POTEN,0); //TEST DE POTENTIOMETRE
}

// Un clique sur le bouton bas droit change l'unité

void QAirSpeed::selectPressed(int num, bool longClic )
{
    m_isUnitKmh = !m_isUnitKmh ;
    updateWithBackground() ;
}

// Potentiomètre

void QAirSpeed::adjustmentChanged(int num, float value )
{
    if (num != POTEN) return ;
    setValue(value,num) ;
    updateWithBackground() ;
}


// dessin d'un arc de cercle ép. 24 px, bouts arrondis

void QAirSpeed::showArc(QPainter& painter, QColor& color, float radius, float start, float span )
{
    painter.save() ;
    QPen pen ;
    pen.setColor( color ) ;
    pen.setWidth(24) ;
    pen.setCapStyle( Qt::RoundCap ) ;
    painter.setPen( pen ) ;
    painter.drawArc(QRect(-radius, -radius, 2 * radius, 2 * radius ), -start * 16, -span * 16 ) ;	// CCW
    painter.restore() ;
}

// dessin d'un texte, positionné par son centre

void QAirSpeed::showText(QPainter& painter, QFont& font, QColor& color, const QPoint& center, const QString& s )
{
    painter.save() ;
    painter.setFont( font ) ;
    painter.setPen( color ) ;
    QRect rText = painter.fontMetrics().boundingRect( s ) ;
    rText.moveCenter( center ) ;
    painter.drawText( rText, Qt::AlignLeft | Qt::AlignVCenter , s ) ;
    painter.restore() ;
}


void QAirSpeed::drawBackground(QPainter& painter )
{
    if (m_isUnitKmh) {
        float w, h ;		// épaisseur et longueur du trait de graduation
        QRect gRect ;		// rectangle "trait graduation"
        float gRadius ;		// arrondi sommets rectangle gRect

        QColor	black1(15,13,11) ;
        QColor	black2(34,32,27) ;
        QColor	white(210,200,190) ;
        QColor	red(221,65,57) ;
        QColor	yellow(205,185,83) ;
        QColor	green(101,149,112) ;

        QFont	fo1("Arial", 60 ) ;
        QFont	fo2("Arial", 50 ) ;


        // fond

        painter.setBrush( black1 ) ;
        painter.drawEllipse( drawingRect() ) ;
        qfiBackground(painter, m_radius[AIRSPEED], 10);

        // zones colorées "Turbine"

        float radius = m_radius[AIRSPEED] - 35 ;

        float start =  -1 ;
        float span = m_step[AIRSPEED] * ( -1.3 ) ;
        qfiArc(painter, yellow, radius, start, span, 24 ) ;

        start += span + 4 ;
        span = m_step[AIRSPEED] * ( (-44.5) / 3 - 0.5 ) ;
        qfiArc(painter, green, radius, start, span, 24 ) ;

        start += span + 4 ;
        span = m_step[AIRSPEED] * (( -1.1  ) / 3 - 0.8 ) ;
        qfiArc(painter, yellow, radius, start, span, 24 ) ;


        //Potentiometre reglage
        start += span - 99 ;
        span = m_step[AIRSPEED] * ( value(POTEN) * (4.8/1000 )) ;
        qfiArc(painter, yellow, radius, start, span, 24 ) ;

        //Trait rouge potentiometre
        setThresholds(16+(value(POTEN)/200),111.5, AIRSPEED ) ;

        // graduations "AIRSPEED" de 0 à 50 km/h

        painter.save() ;
        painter.setBrush( red ) ;

        painter.rotate(90 ) ;


        for ( int i = 0 ; i <= ( 2 ) ; ++i ) {

            if ( i % 5 == 0 ) {		w = 20 ; h = 20 ; }
                else {						w =  10 ; h = 40 ;
                painter.setBrush( white ) ;}

            gRect = QRect(m_radius[AIRSPEED] - h - 10, -w / 2, h, w) ;
            gRadius = w / 3 ;
            painter.drawRoundedRect(gRect, gRadius, gRadius ) ;
            painter.rotate( 10 ) ;
        }
        painter.restore() ;

        // graduations "AIRSPEED" de 50 à 250 km/h

        painter.save() ;
        painter.setBrush( white ) ;

        painter.rotate( m_start[AIRSPEED] ) ;

        for ( int i = 0 ; i <= ( 1+m_max[AIRSPEED] - m_min[AIRSPEED] ) ; ++i ) {

            if ( i % 5 == 0 ) {		w = 20 ; h = 70 ; }
                else {						w =  10 ; h = 40 ; }

            gRect = QRect(m_radius[AIRSPEED] - h - 10, -w / 2, h, w) ;
            gRadius = w / 3 ;
            painter.drawRoundedRect(gRect, gRadius, gRadius ) ;
            painter.rotate( m_step[AIRSPEED] ) ;
        }
        painter.restore() ;




        // sérigraphie "AIRSPEED"
        for ( int i = 5 ; i <= ( 25 - m_min[AIRSPEED] ) ; i += 5 ) {
            float alpha = qDegreesToRadians( 45 + i * m_step[AIRSPEED] ) ;
            float r = m_radius[AIRSPEED] - 170 ;
            showText(painter, fo1, white, QPoint( r * qCos(alpha), r * qSin(alpha) ), QString("%1").arg(i*10) ) ;
        }

        setLabel(QString("km/h"), AIRSPEED ) ;
        showText(painter, fo2, white, QPoint( 0, 0.3 * m_radius[AIRSPEED] ), label(AIRSPEED) ) ;
       // showText(painter, fo2, white, QPoint( 0, 0.3 * m_radius[AIRSPEED] ), unit(AIRSPEED) ) ;


        // seuils "AIRSPEED"

        w = 20 ; h = 90 ;
        gRect = QRect(m_radius[AIRSPEED] - h - 10, -w / 2, h, w ) ;
        gRadius = w / 3 ;

        painter.save() ;
        painter.setBrush( red ) ;
        painter.rotate(m_start[AIRSPEED] + m_step[AIRSPEED] * lowThreshold(AIRSPEED)  ) ;
        painter.drawRoundedRect(gRect, gRadius, gRadius ) ;
        painter.restore() ;

        }


    else {


        float w, h ;		// épaisseur et longueur du trait de graduation
        QRect gRect ;		// rectangle "trait graduation"
        float gRadius ;		// arrondi sommets rectangle gRect

        QColor	black1(15,13,11) ;
        QColor	black2(34,32,27) ;
        QColor	white(210,200,190) ;
        QColor	red(221,65,57) ;
        QColor	yellow(205,185,83) ;
        QColor	green(101,149,112) ;

        QFont	fo1("Arial", 60 ) ;
        QFont	fo2("Arial", 50 ) ;



        // fond

        painter.setBrush( black1 ) ;
        painter.drawEllipse( drawingRect() ) ;
        qfiBackground(painter, m_radius[AIRSPEED], 10);

        // zones colorées "Turbine"

        float radius = m_radius[AIRSPEED] - 35 ;

        float start =  -9.5 ;
        float span = m_step[AIRSPEED] * ( -1.6 ) ;
        qfiArc(painter, yellow, radius, start, span, 24 ) ;

        start += span +11 ;
        span = m_step[AIRSPEED] * ( (-43.5) / 3 - 0.5 ) ;
        qfiArc(painter, green, radius, start, span, 24 ) ;

        start += span -1 ;
        span = m_step[AIRSPEED] * (( 5.5  ) / 9 ) ;
        qfiArc(painter, yellow, radius, start, span, 24 ) ;

        //Potentiometre reglage zone colorée rouge
        start += span - 129 ;
        span = m_step[AIRSPEED] * ( value(POTEN) * (4.8/1000 )) ;
        qfiArc(painter, yellow, radius, start, span, 24 ) ;


        // graduations "AIRSPEED" de 0 à 50 km/h

        painter.save() ;
        painter.setBrush( white ) ;

        painter.rotate(110 ) ;


        for ( int i = 0 ; i <= ( 24 ) ; ++i ) {

            if ( i % 4 == 0 ) {		w = 20 ; h = 60 ; }
          /*  else if ( i % 5 == 0 ) {	w = 10 ; h = 60 ; } */
           else {						w =  10 ; h = 40 ;
                painter.setBrush( white ) ;}

            gRect = QRect(m_radius[AIRSPEED] - h - 10, -w / 2, h, w) ;
            gRadius = w / 3 ;
            painter.drawRoundedRect(gRect, gRadius, gRadius ) ;
            painter.rotate( 13 ) ;
        }
        painter.restore() ;



        // sérigraphie "AIRSPEED"
        for ( int i = 2 ; i <= ( 14 - m_min[AIRSPEED] ) ; i += 2 ) {
            float alpha = qDegreesToRadians( 60 + i * m_step2[AIRSPEED] ) ;
            float r = m_radius[AIRSPEED] - 170 ;
            showText(painter, fo1, white, QPoint( r * qCos(alpha), r * qSin(alpha) ), QString("%1").arg(i*10) ) ;
        }


        setLabel(QString("Knots"), AIRSPEED ) ;
        showText(painter, fo2, white, QPoint( 0, 0.3 * m_radius[AIRSPEED] ), label(AIRSPEED) ) ;
       // showText(painter, fo2, white, QPoint( 0, 0.3 * m_radius[AIRSPEED] ), unit(AIRSPEED) ) ;


        // seuils "AIRSPEED"

        w = 20 ; h = 90 ;
        gRect = QRect(m_radius[AIRSPEED] - h - 10, -w / 2, h, w ) ;
        gRadius = w / 3 ;

        painter.save() ;
        painter.setBrush( red ) ;
        painter.rotate(-9+(value(POTEN)*74/1000)  ) ;
        painter.drawRoundedRect(gRect, gRadius, gRadius ) ;
        painter.restore() ;

    }
    }

void QAirSpeed::drawForeground(QPainter& painter )
    {

        float len ;						// longueur de l'aiguille orientée 0X+
        QVector<QPointF> pts ;			// points de construction dans demi-plan 0Y+
        QColor white(230,230,230) ;		// couleur de la pointe

        // aiguille "Rotor"

        len = 0.95 * m_radius[AIRSPEED] ;
        pts.clear() ;
        pts << QPointF( -164, 55 ) << QPointF( -162, 65 ) << QPointF( -160, 75 ) << QPointF( -155, 80 ) << QPointF( -150, 85 ) << QPointF( -145, 90 ) << QPointF( -135, 90 ) << QPointF( -20, 15 )<< QPointF( len - 60, 15 ) << QPointF( len, 0 ) ;

        painter.save() ;


        float f=value(AIRSPEED);

        if (m_isUnitKmh==true){
            if ( f <= 26.9978 ) {
                painter.rotate(90 +( (f*1.852) *6 /10.0 ) ) ;
            }
            else {
                painter.rotate(45 +( (f*1.852) *15 /10.0 ) ) ;
            }
        }
        else {
            if ( f<=20 ) {
                painter.rotate(90 +( f ) ) ;
            }
            else {
                painter.rotate(57 +( f * 52.3 /20.0 ) ) ;
            }
        }


        qfiNeedle(painter, white, pts, 30, 0, 0.01*len ) ;

        //painter.drawPath( path ) ;

        painter.restore() ;

        // axe central

        int axeRadius = 30 ;

        QConicalGradient	cg(QPointF(0.0, 0.0 ), 360 ) ;
        cg.setColorAt(0.0, Qt::white ) ;
        cg.setColorAt(0.5, Qt::black ) ;
        cg.setColorAt(1.0, Qt::white ) ;

        painter.save() ;
        painter.rotate(-135) ;
        painter.setPen(Qt::black ) ;
        painter.setBrush(QBrush( cg ) ) ;
        painter.drawEllipse(-axeRadius, -axeRadius, 2 * axeRadius, 2 * axeRadius ) ;
        axeRadius /= 3 ;
        painter.rotate(180 ) ;
        painter.setPen(Qt::NoPen ) ;
        painter.drawEllipse(-axeRadius, -axeRadius, 2 * axeRadius, 2 * axeRadius ) ;
        painter.restore() ;

}

