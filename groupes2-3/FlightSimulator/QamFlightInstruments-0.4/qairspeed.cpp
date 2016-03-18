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
    /*setUnit(QString("x 1000"), AIRSPEED ) ;*/
    setMinMax(0, 140, AIRSPEED ) ;
    setThresholds(16,111.5, AIRSPEED ) ;
    setValue(0, AIRSPEED ) ;

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
    connect(this, SIGNAL( selectChanged() ), this, SLOT( selectChanged() ) ) ;
}

// Un clique sur le bouton bas droit change l'unité

void QAirSpeed::selectPressed(int num, bool longClic )
{
    m_isUnitKmh = !m_isUnitKmh ;
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

        // graduations "AIRSPEED" de 0 à 50 km/h

        painter.save() ;
        painter.setBrush( red ) ;

        painter.rotate(90 ) ;


        for ( int i = 0 ; i <= ( 2 ) ; ++i ) {

            if ( i % 5 == 0 ) {		w = 20 ; h = 20 ; }
          /*  else if ( i % 5 == 0 ) {	w = 10 ; h = 60 ; } */
           else {						w =  4 ; h = 40 ;
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
           else {						w =  4 ; h = 40 ; }

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
       // float radius = m_radius[ROTOR] + 45 ;
    /*
        painter.setBrush( QBrush( black2 ) ) ;
        painter.drawEllipse( QRect(-radius, -radius, 2 * radius, 2 * radius ) ) ;
    */
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


        // graduations "AIRSPEED" de 0 à 50 km/h

        painter.save() ;
        painter.setBrush( white ) ;

        painter.rotate(110 ) ;


        for ( int i = 0 ; i <= ( 24 ) ; ++i ) {

            if ( i % 4 == 0 ) {		w = 20 ; h = 60 ; }
          /*  else if ( i % 5 == 0 ) {	w = 10 ; h = 60 ; } */
           else {						w =  4 ; h = 40 ;
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
        painter.rotate(m_start[AIRSPEED] + m_step[AIRSPEED] * highThreshold(AIRSPEED)  ) ;
        painter.drawRoundedRect(gRect, gRadius, gRadius ) ;
        painter.restore() ;

    }
    }

    void QAirSpeed::drawForeground(QPainter& painter )
    {
        float e ;	// épaisseur aiguille
        float lp ;	// longueur de la pointe
        float l1 ;	// longueur avant (coté pointe)
        float l2 ;	// longueur arrière
        float r1 ;	// rayon central
        float r2 ;	// rayon du contrepoids

        QPolygonF needle ;


        // aiguille "AIRSPEED"

        e = 30 ;
        lp = 2 * e ;
        l1 = m_radius[AIRSPEED] - 90 ;
        l2 = m_radius[AIRSPEED] - 350 ;
        r1 = 40 ;
        r2 = 80 ;

        needle.clear() ;
        needle << QPointF(-l2,-100) << QPointF(-50,-e/2) << QPointF(l1-lp,-e/2) << QPointF(l1,0) << QPointF(l1-lp,e/2) << QPointF(-50,e/2) << QPointF(-l2,100) ;

        QPainterPath	path ;

        path.setFillRule(Qt::WindingFill) ;
        path.addEllipse(-r1, -r1, 2*r1, 2*r1 ) ;
        path.addPolygon( needle ) ;

        painter.save() ;
        painter.setPen(Qt::NoPen) ;
        painter.setBrush( QColor(200, 200, 200, 120 ) ) ;

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



        painter.drawPath( path ) ;

        painter.restore() ;

        // axe central

        int axeRadius = 30 ;

        QConicalGradient	cg(QPointF(0.0, 0.0 ), 360 ) ;
        cg.setColorAt(0.0, Qt::white ) ;
        cg.setColorAt(0.5, Qt::black ) ;
        cg.setColorAt(1.0, Qt::white ) ;

        painter.save() ;
        painter.rotate(-135 ) ;
        painter.setPen(Qt::black ) ;
        painter.setBrush(QBrush( cg ) ) ;
        painter.drawEllipse(-axeRadius, -axeRadius, 2 * axeRadius, 2 * axeRadius ) ;
        axeRadius /= 3 ;
        painter.rotate(180 ) ;
        painter.setPen(Qt::NoPen ) ;
        painter.drawEllipse(-axeRadius, -axeRadius, 2 * axeRadius, 2 * axeRadius ) ;
        painter.restore() ;
}
