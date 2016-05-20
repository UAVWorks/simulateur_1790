/*  ---------------------------------------------------------------------------
 *  filename    :   qvariometer.cpp
 *  description :   IMPLEMENTATION de la classe QamVariometer
 *
 *  project     :   Widgets "Flight Instrument"
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
 *  You should have  received  a copy of the  GNU General Public License  along
 *  with this program. If not, see <http://www.gnu.org/licenses/>.
 *  ---------------------------------------------------------------------------
 */

#include "qvariometer.h"

#include <QtMath>
#include <QLabel>

QamVariometer::QamVariometer(QWidget* parent ) : QamFlightInstrument(parent)
{
    setLabel(QString(" Vertical Speed "), VARIOMETER) ;
    setUnit(QString("ft/min x100"), VARIOMETER) ;
    setMinMax(-2000, 2000, VARIOMETER) ;
    setValue(0, VARIOMETER) ;

    m_radius[VARIOMETER] = QFI_RADIUS ;
    m_start[VARIOMETER]  = 10 ;
    m_span[VARIOMETER]   = 340 ;
    m_min[VARIOMETER]    = -20 ;
    m_max[VARIOMETER]    = 20 ;
    m_step[VARIOMETER]   = m_span[VARIOMETER] / ( m_max[VARIOMETER] - m_min[VARIOMETER] ) ;

    // changeunit

    setLabel(QString("Vertical Speed"), CHANGEUNIT);
    setUnit(QString("m/s"), CHANGEUNIT) ;
    setMinMax(-10, 10, CHANGEUNIT) ;
    setValue(0, CHANGEUNIT) ;

    m_radius[CHANGEUNIT] = QFI_RADIUS ;
    m_start[CHANGEUNIT]  = 10 ;
    m_span[CHANGEUNIT]   = 340 ;
    m_min[CHANGEUNIT]    = -10 ;
    m_max[CHANGEUNIT]    = 10 ;
    m_step[CHANGEUNIT]   = m_span[CHANGEUNIT] / ( m_max[CHANGEUNIT] - m_min[CHANGEUNIT] ) ;

//  animation des aiguilles (pour tests)

    setAdjustable(1, 0, VARIOMETER) ;
}

// interception clic sur BP coin inférieur droit

void QamVariometer::selectPressed(int num, bool longClic)
{
    m_isUnitMS = !m_isUnitMS;
    updateWithBackground();
}

// dessin d'un arc de cercle ép. 24 px, bouts arrondis

void QamVariometer::showArc(QPainter& painter, QColor& color, float radius, float start, float span )
{
    painter.save() ;
    QPen pen ;
    pen.setColor( color ) ;
    pen.setWidth(24) ;
    pen.setCapStyle( Qt::RoundCap ) ;
    painter.setPen( pen ) ;
    painter.drawArc(QRect(-radius, -radius, 2 * radius, 2 * radius ), -start * 16, -span * 16 ) ;   // CCW
    painter.restore() ;
}

// dessin d'un texte, positionné par son centre

void QamVariometer::showText(QPainter& painter, QFont& font, QColor& color, const QPoint& center, const QString& s )
{
    painter.save() ;
    painter.setFont( font ) ;
    painter.setPen( color ) ;
    QRect rText = painter.fontMetrics().boundingRect( s ) ;
    rText.moveCenter( center ) ;
    painter.drawText( rText, Qt::AlignTop | Qt::AlignRight , s ) ;
    painter.restore() ;
}

void QamVariometer::drawBackground(QPainter& painter )
{
    float w, h ;        // épaisseur et longueur du trait de graduation
    QRect gRect ;       // rectangle "trait graduation"
    float gRadius ;     // arrondi sommets rectangle gRect

    QColor  black1(15,13,11) ;
    QColor  black2(34,32,27) ;
    QColor  white(210,200,190) ;
    QColor  red(221,65,57) ;
    QColor  yellow(205,185,83) ;
    QColor  green(101,149,112) ;

    QFont   fo1("Arial", 60 ) ;
    QFont   fo2("Arial", 50 ) ;
    QFont   fo3("Arial", 40 ) ;
    QFont   fo4("Arial", 45 ) ;
    QFont   fo5("Arial", 35 ) ;

    QRectF rectangle(10.0, 20.0, 80.0, 60.0);
    int startAngle = 30 * 16;
    int spanAngle = 120 * 16;



    if (m_isUnitMS) {

        // fond

        painter.setBrush( black1 ) ;
        painter.drawEllipse( drawingRect() ) ;

        painter.setBrush( QBrush( black2 ) ) ;
        qfiBackground(painter, m_radius[VARIOMETER]);
        painter.save();

        // dessin arc de cercle
        QPen pen(white);
        pen.setWidth(5);

        painter.setPen(pen);
        painter.setBrush(Qt::white);
        painter.drawArc(-0.836*QFI_RADIUS, -0.836*QFI_RADIUS, 1.7*QFI_RADIUS,1.7*QFI_RADIUS,16*165,16*30);
        painter.restore();

        /* static const QPointF points[3] = {
            QPointF(10.0, 80.0),
            QPointF(20.0, 10.0),
            QPointF(80.0, 30.0),
        };

        QPainter painter(this);
        painter.drawPolygon(points, 3); */


        // graduations

        painter.save() ;
        painter.setBrush( white ) ;

        painter.rotate( m_start[VARIOMETER] ) ;

        for ( int i = 0 ; i <= ( m_max[VARIOMETER] - m_min[VARIOMETER] ) ; ++i ) {

            if ( i % 5 == 0 ) {     w = 10 ; h = 60 ; }
            else {                      w =  4 ; h = 40 ; }

            gRect = QRect(m_radius[VARIOMETER] - h - 10, -w / 2, h, w) ;
            gRadius = w / 3 ;
            painter.drawRoundedRect(gRect, gRadius, gRadius ) ;
            painter.rotate( m_step[VARIOMETER] ) ;
        }
        painter.restore() ;

        // sérigraphie

        for ( int i = 20 ; i >= ( 0 ) ; i += -5 ) {
            float alpha = -qDegreesToRadians( 180 + i * m_step[VARIOMETER] ) ;
            float r = m_radius[VARIOMETER] - 130 ;
            showText(painter, fo1, white, QPoint( r * qCos(alpha), r * qSin(alpha) ), QString("%1").arg(i) ) ;
        }

        for ( int i = 0 ; i <= ( 20 ) ; i += 5 ) {
            float alpha = qDegreesToRadians( 180 + i * m_step[VARIOMETER] ) ;
            float r = m_radius[VARIOMETER] - 130 ;
            showText(painter, fo1, white, QPoint( r * qCos(alpha), r * qSin(alpha) ), QString("%1").arg(i) ) ;
        }
        showText(painter, fo2, white, QPoint( 0, -0.3 * m_radius[VARIOMETER] ), label(VARIOMETER) ) ;
        showText(painter, fo3, white, QPoint( 0, 0.4 * m_radius[VARIOMETER] ), unit(VARIOMETER) ) ;

    }

else {
    // fond

    painter.setBrush( black1 ) ;
    painter.drawEllipse( drawingRect() ) ;

    painter.setBrush( QBrush( black2 ) ) ;
    qfiBackground(painter, m_radius[CHANGEUNIT]);

    // graduations

    painter.save() ;
    painter.setBrush( white ) ;

    painter.rotate( m_start[CHANGEUNIT] ) ;

    for ( int i = 0 ; i <= ( 30 ) ; ++i ) {

        if ( i % 3 == 0 ) {     w = 10 ; h = 60 ; }
        else {                      w =  4 ; h = 40 ; }

        gRect = QRect(m_radius[CHANGEUNIT] - h - 10, -w / 2, h, w) ;
        gRadius = w / 3 ;
        painter.drawRoundedRect(gRect, gRadius, gRadius ) ;
        painter.rotate( 11.3 ) ;
    }
    painter.restore() ;

    // dessin arc de cercle
    QPen pen(white);
    pen.setWidth(5);

    painter.setPen(pen);
    painter.setBrush(Qt::white);
    painter.drawArc(-0.836*QFI_RADIUS, -0.836*QFI_RADIUS, 1.7*QFI_RADIUS,1.7*QFI_RADIUS,16*165,16*30);
    painter.restore();

    // sérigraphie

    for ( int i = 10 ; i >= ( 0 ) ; i += -2 ) {
        float alpha = -qDegreesToRadians( 180 + i * m_step[CHANGEUNIT] ) ;
        float r = m_radius[CHANGEUNIT] - 130 ;
        showText(painter, fo1, white, QPoint( r * qCos(alpha), r * qSin(alpha) ), QString("%1").arg(i) ) ;
    }

    for ( int i = 0 ; i <= ( 10 ) ; i += 2 ) {
        float alpha = qDegreesToRadians( 180 + i * m_step[CHANGEUNIT] ) ;
        float r = m_radius[CHANGEUNIT] - 130 ;
        showText(painter, fo1, white, QPoint( r * qCos(alpha), r * qSin(alpha) ), QString("%1").arg(i) ) ;
    }
    showText(painter, fo2, white, QPoint( 0, -0.3 * m_radius[CHANGEUNIT] ), label(CHANGEUNIT) ) ;
    showText(painter, fo3, white, QPoint( 0, 0.4 * m_radius[CHANGEUNIT] ), unit(CHANGEUNIT) ) ;

}
    }

void QamVariometer::drawForeground(QPainter& painter )
{
    float e ;   // épaisseur aiguille
    float lp ;  // longueur de la pointe
    float l1 ;  // longueur avant (coté pointe)
    float l2 ;  // longueur arrière
    float r1 ;  // rayon central
    float r2 ;  // rayon du contrepoids

    QPolygonF needle ;

    // aiguille

    e = 22 ;
    lp = 1.3 * e ;
    l1 = m_radius[VARIOMETER] - 160 ;
    l2 = m_radius[VARIOMETER] - 410 ;
    r1 = 10 ;
    r2 = 0 ;

    needle.clear() ;
    needle << QPointF(-l2,-e/2) << QPointF(l1-lp,-e/2) << QPointF(l1,0) << QPointF(l1-lp,e/2) << QPointF(-l2,e/2) ;

    QPainterPath    path ;

    path.setFillRule(Qt::WindingFill) ;
    path.addEllipse(-r2-l2, -r2-2, 2*r2, 2*r2 ) ;
    path.addEllipse(-r1, -r1, 2*r1, 2*r1 ) ;
    path.addPolygon( needle ) ;

    painter.save() ;
    painter.setPen(Qt::NoPen) ;
    painter.setBrush( Qt::white) ;
    painter.rotate(180 + value(VARIOMETER) * 0.085) ;



    painter.drawPath( path ) ;

    painter.restore() ;

    // axe central

    int axeRadius = 20;

    QConicalGradient    cg(QPointF(0.0, 0.0 ), 360 ) ;
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

