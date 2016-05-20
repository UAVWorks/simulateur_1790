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

    m_timer->start(100) ;	// période 1 seconde

	// BP --> 3-function operating knob (start-stop-reset)
    setAdjustable(1000, 0, MINUTE ) ;
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

// dessin de la partie mobile

void QHA::drawBackground(QPainter& painter ){

}



void QHA::drawForeground(QPainter& painter )
{
    QColor	black1(230,230,230) ;
    QColor	black2(160,160,160) ;
    QColor	yellow(250,250,0) ; //couleur triangle
    QColor  white (250,250,250);
    QFont	fo1("Arial", 100 ) ;
    QFont	fo2("Arial", 50 ) ;
    QColor  bleuexterieur (83,123,216);
    QColor  marronexterieur (76,36,11);
    QColor  bleuinterieur (83,123,216);
    QColor  marroninterieur (76,36,11);

    // fond


    qfiBackground(painter, m_radius[HOUR], 100) ;

        QConicalGradient cg(QPointF(0.0, 0.0), 360 ) ;
        cg.setColorAt(0.0, Qt::white ) ;
        cg.setColorAt(1.0, QColor (139,69,19) ) ;

        //pies bague
        painter.save();
        painter.setBrush(bleuexterieur);
                                        //largeur                hauteur              élargie largeur        elargie hauteur
        painter.drawPie             (-0.831*QFI_RADIUS,     -0.83*QFI_RADIUS,       2.075*0.8*QFI_RADIUS,    2.07*0.8*QFI_RADIUS,    16*0,16*180);
        painter.restore();


        painter.save();
        painter.setBrush(marronexterieur);
        painter.drawPie               (-0.831*QFI_RADIUS,-0.83*QFI_RADIUS, 2.075*0.8* QFI_RADIUS,   2.08*0.8 * QFI_RADIUS,   16*180,16*180);
        painter.restore();

        //pies rond central




        painter.save();
        painter.setBrush(bleuinterieur);
                                  //largeur             hauteur                élargie largeur                 elargie hauteur
        painter.drawPie     (-0.635*QFI_RADIUS,     -0.64*QFI_RADIUS,       1.59*0.8*QFI_RADIUS,           1.61*0.8*QFI_RADIUS,     16*0,16*180);
        painter.restore();


        painter.save();
        painter.setBrush(marroninterieur);
        painter.drawPie               (-0.635*QFI_RADIUS,-0.63*QFI_RADIUS, 1.59*0.8* QFI_RADIUS,   1.58*0.8 * QFI_RADIUS,      16*180,16*180);
        painter.restore();




        //triangles
        float w = 0;
        float h = 30;
        float r = 0.64*QFI_RADIUS;
        float hbis = h + 5 ;
        QPolygon    triangle, triangle2, triangle3;


    triangle    << QPoint ( r, 0) << QPoint (r + 1.5 * hbis, - 0.75 * hbis) << QPoint(r + 1.5 * hbis, 0.75* hbis) ;
    triangle2 << QPoint ( r, 0) << QPoint (0.82*QFI_RADIUS, - hbis) << QPoint(0.82*QFI_RADIUS, hbis) ;
    triangle3 << QPoint ( r, 0) << QPoint (0.45*QFI_RADIUS, - hbis) << QPoint(0.45*QFI_RADIUS, hbis );





  painter.save();

  painter.rotate(-90);

        for ( int i = 0 ; i < 360 ; ++i) {
            painter.save();
            painter.setBrush(white);
  if (i == 0) painter.drawConvexPolygon(triangle2);
  painter.restore();

  painter.save();
  painter.setBrush(yellow);

  if (i == 0) painter.drawConvexPolygon(triangle3);
  painter.restore();

  painter.save();
  painter.setBrush(white);
   if (i == 45)painter.drawConvexPolygon(triangle);
   if (i == 315)painter.drawConvexPolygon(triangle);// By Axel
  painter.restore();

    if (i % 5 == 0)   painter.drawRect(r, 10000, hbis, hbis );
    else if (i % 5 == 0 )   painter.drawEllipse(r, 10000, hbis, hbis);
    else                      qfiMarker(painter, white, r + h, QSize(w, h) ) ;
    painter.rotate(1.0) ;
        }
        painter.restore();



        //2 lignes rond central

        painter.setPen(QPen(Qt::white,3));
        painter.drawLine(-355, 0, 355, 0);
        painter.drawLine(-45, -150, 45, -150); //1 ligne (P)
        painter.drawLine(-45, -100, 45, -100); //2 ligne (P)



    // graduations
        painter.save() ;
        painter.rotate(180.0) ;
        QPen pen( Qt::white ) ;
        pen.setWidth(5) ;
        painter.setPen( pen ) ;
        for ( int i = 0 ; i < 31 ; ++i ) {
            int len = ( (i % 5) == 0 ? 90: 0 ) ;
            if (i != 15){
                if (( i== 12) || (i == 13) | (i == 17) || (i == 18 ))
                    len = 45 ;

            if (len != 0)
                painter.drawLine(0.82 * QFI_RADIUS - 90, 0,0.82 * QFI_RADIUS - 90 + len, 0 );
            }
            painter.rotate(6.0) ;
        }
        painter.restore() ;
    }
