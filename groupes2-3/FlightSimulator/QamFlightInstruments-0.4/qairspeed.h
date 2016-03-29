/*  ---------------------------------------------------------------------------
 *  filename    :   qairspeed.h
 *  description :   INTERFACE de la classe QamTachymeter
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

// Source: Indicateur Tachymétrique KEHA Präcitechnik AMA ref. 8-436-AB type 901F
//Test
#ifndef QAIRSPEED_H
#define QAIRSPEED_H

#include "qflightinstrument.h"

class QAirSpeed : public QFlightInstrument
{
    Q_OBJECT

  public:
    explicit QAirSpeed(QWidget* parent = 0 ) ;

    enum Axis{ AIRSPEED, POTEN } ;

  protected:
    virtual void drawBackground(QPainter& painter ) ;
    virtual void drawForeground(QPainter& painter ) ;

  private slots:
//    void selectChanged() ;
    virtual void selectPressed(int num, bool longClic = false ) ;
    virtual void adjustmentChanged(int num, float value ) ;

  private:
    void showArc(QPainter&, QColor&, float, float, float ) ;
    void showText(QPainter&, QFont&, QColor&, const QPoint&, const QString& ) ;

  private:
    float	m_radius[2] ;	// rayon ext. graduation
    float	m_start[2] ;	// angle de l'origine (p/r 3 o'clock)
    float	m_span[2] ;		// amplitude angulaire totale
    float	m_span2[2] ;
    float	m_step[2] ;		// pas des graduations
    float	m_step2[2] ;
    float	m_min[2] ;		// graduation minimale
    float	m_max[2] ; 		// graduation maximale

    bool    m_isUnitKmh ;

} ;

#endif
