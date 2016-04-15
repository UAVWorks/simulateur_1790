/*  ---------------------------------------------------------------------------
 *  filename    :   QamGyroDir.cpp
 *  description :   IMPLEMENTATION de la classe QamGyroDir
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

#include "qamgyrodir.h"
#include <QtMath>

QamGyroDir::QamGyroDir(QWidget* parent ) : QamFlightInstrument(parent)
{
    m_class = "QamGyroDir" ;
    
    //setLabel(QString("GYRDIR"), GYRDIR ) ;
    //setUnit(QString("x 1000"), GYRDIR ) ;
    //setMinMax(0 , 0, GYRDIR ) ;
    //setThresholds(32000, 35000, GYRDIR ) ;
    setValue(0, GYRDIR ) ;

    m_radius[GYRDIR] = QFI_RADIUS ;
    m_start[GYRDIR]  = 90 ;
    m_span[GYRDIR]   = 360 ;
    m_min[GYRDIR]    =   0 ;
    m_max[GYRDIR]    =  72 ;
    m_step[GYRDIR]   = m_span[GYRDIR] / ( m_max[GYRDIR] - m_min[GYRDIR] ) ;


    //  animation des aiguilles (pour tests)
    
    setAdjustable(3, 0, GYRDIR ) ;
}

// interception clic sur BP coin inférieur droit

void QamGyroDir::adjustmentChanged(int num, float value )
{
    setValue( value, num ) ;
}

void QamGyroDir::drawBackground(QPainter& painter )
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

    // fond

    qfiBackground(painter, m_radius[GYRDIR], 10 ) ;

    // avion

    float wi = 2000 ;
// image width
        float hi = 2000  ;
// image height
        float si = 2000 ;
// scale
        QRectF target(-0.65*QFI_RADIUS,-0.65*QFI_RADIUS, 5.1*(QFI_RADIUS), 5.1*QFI_RADIUS) ;
        QRectF source(1.0, 1.0, wi, hi ) ;
        QImage image("C:/Users/Romain/Downloads/roro.png") ;
        painter.drawImage(target, image, source ) ;



    // seuils "GYRDIR"
    
     /*
    w = 20 ; h = 90 ;
    
    painter.save() ;
    painter.rotate(m_start[GYRDIR] + m_step[GYRDIR] * lowThreshold(GYRDIR) / 1000 ) ;
    qfiMarker(painter, red, m_radius[GYRDIR] - 10, QSize(w, h ) ) ;
    painter.restore() ;
    
    painter.save() ;
    painter.rotate(m_start[GYRDIR] + m_step[GYRDIR] * highThreshold(GYRDIR) / 1000 ) ;
    qfiMarker(painter, red, m_radius[GYRDIR] - 10, QSize(w, h ) ) ;
    painter.restore() ;

    */

    // zones colorées "GYRDIR"


   // float radius = m_radius[GYRDIR] - 80 ;

    //float start = m_start[GYRDIR] + m_step[GYRDIR] * lowThreshold(GYRDIR) / 100 + 4 ;
    //float span = m_step[GYRDIR] * ( ( ( highThreshold(GYRDIR) - lowThreshold(GYRDIR) ) / 1000 ) / 3 - 0.75 ) ;
   /* qfiArc(painter, yellow, radius, start, span, 24 ) ;

    start += span + 4 ;
    span = m_step[GYRDIR] * ( ( ( highThreshold(GYRDIR) - lowThreshold(GYRDIR) ) / 1000 ) / 3 - 0.5 ) ;
    qfiArc(painter, green, radius, start, span, 24 ) ;

    start += span + 4 ;
    span = m_step[GYRDIR] * ( ( ( highThreshold(GYRDIR) - lowThreshold(GYRDIR) ) / 1000 ) / 3 - 0.8 ) ;
    qfiArc(painter, yellow, radius, start, span, 24 ) ;

    */

    // graduations "Rotor"
    /*

    painter.save() ;
    
    radius = m_radius[ROTOR] ;
    qfiArc(painter, white, radius, m_start[ROTOR], m_span[ROTOR], 5 ) ;

    QPen pen( white ) ;
    pen.setWidth(1) ;
    painter.setPen( pen ) ;
    painter.setBrush( white ) ;

    painter.rotate( m_start[ROTOR] ) ;
    
    for ( int i = 0 ; i <= ( m_max[ROTOR] - m_min[ROTOR] ) ; ++i ) {

        if ( i % 5 == 0 ) { w = 10 ; h = 60 ; }
        else {              w =  6 ; h = 40 ; }

        qfiMarker(painter, white, m_radius[ROTOR], QSize(w, h ) ) ;
        
        painter.rotate( m_step[ROTOR] ) ;
    }
    
    */
    //painter.restore() ;

    // sérigraphie "Rotor"

    /*
        
    for ( int i = 0 ; i <= ( m_max[ROTOR] - m_min[ROTOR] ) ; i += 10 ) {
        float alpha = qDegreesToRadians( m_start[ROTOR] + i * m_step[ROTOR] ) ;
        float r = m_radius[ROTOR] - 90 ;
        qfiText(painter, fo2, white, QPoint( r * qCos(alpha), r * qSin(alpha) ), QString("%1").arg(i/10) ) ;
    }
    qfiText(painter, fo1, white, QPoint( 0,  m_radius[ROTOR] / 4 ), label(ROTOR) ) ;
    qfiText(painter, fo2, white, QPoint( 0, -m_radius[ROTOR] / 4 ), unit(ROTOR) ) ;

    */
    
    // seuils "Rotor"


    // zones colorées "Rotor"

    /*

    radius = m_radius[ROTOR] + 25 ; 
    
    start = m_start[ROTOR] + m_step[ROTOR] * lowThreshold(ROTOR) / 10 + 5 ;
    span = m_step[ROTOR] * 3.5 ;
    qfiArc(painter, yellow, radius, start, span, 24 ) ;

    start += span + 5 ;
    span = m_step[ROTOR] * ( ( highThreshold(ROTOR) - lowThreshold(ROTOR) ) / 10 - 5.5 ) ;
    qfiArc(painter, green, radius, start, span, 24 ) ; */
}

void QamGyroDir::drawForeground(QPainter& painter )
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

    // graduations "GYRDIR"

    painter.save() ;
    painter.setBrush( white ) ;

    painter.rotate( m_start[GYRDIR] + value(GYRDIR) - 90) ;


    for ( int i = 0 ; i < ( (m_max[GYRDIR] - m_min[GYRDIR])  ) ; ++i ) {

        if ( i % 2 == 0 ) {     w = 7 ; h = 50 ; }
        else {                      w =  4 ; h = 25 ; }

        gRect = QRect(m_radius[GYRDIR] - h - 10, -w / 2, h, w) ;
        gRadius = w / 3 ;
        painter.drawRoundedRect(gRect, gRadius, gRadius ) ;
        // sérigraphie
        if (i%6 == 0){
            float alpha = qDegreesToRadians( m_start[GYRDIR] + m_step[GYRDIR] ) ;
            float r = m_radius[GYRDIR] - 120 ;
            qfiText(painter, fo1, white, QPoint( r * qCos(alpha)+35, r * qSin(alpha) ), QString("%1").arg(i/2) ) ;
        }
        painter.rotate( m_step[GYRDIR] ) ;

    }
    painter.restore() ;




    //qfiText(painter, fo1, white, QPoint( 0, 0.8 * m_radius[GYRDIR] ), label(GYRDIR) ) ;
    //qfiText(painter, fo2, white, QPoint( 0, 0.9 * m_radius[GYRDIR] ), unit(GYRDIR) ) ;
}

