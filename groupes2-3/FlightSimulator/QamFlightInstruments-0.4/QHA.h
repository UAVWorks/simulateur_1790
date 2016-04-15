/*  ---------------------------------------------------------------------------
 *  filename    :   QHA.h
 *  description :   INTERFACE de la classe QHA
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

#ifndef QHA_H
#define QHA_H

#include "qamflightinstrument.h"
#include <QTimer>
#include <QTime>
#include <QColor>

class QHA : public QamFlightInstrument
{
	Q_OBJECT

  public:
    explicit QHA(QWidget* parent = 0 ) ;

	enum Axis { HOUR, MINUTE, ELAPSEDMIN, ELAPSEDSEC } ;
	enum State { STOP, START, RESET } ;
	
	void setAutoTime(bool autoTime = true ) ;
	bool isAutoTime() const ;

  private slots:
	void timeout() ;
	void selectChanged() ;

  protected:
	virtual void drawBackground(QPainter& painter ) ;
	virtual void drawForeground(QPainter& painter ) ;

  private:
	QTimer*	m_timer ;
	State	m_elapsedTimeState ;
	
	float	m_sec ;			// secondes horloge principale
	bool	m_autoTime ;	// heure courante automatique
	float	m_radius[2] ;	// HOUR & MINUTE
} ;

#endif // QCHRONOGRAPH_H
