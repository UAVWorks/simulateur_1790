/*  ---------------------------------------------------------------------------
 *  filename    :   qamturncoordinator.h
 *  description :   INTERFACE de la classe QamTurnCoordinator
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

#ifndef QAMTURNCOORDINATOR_H
#define QAMTURNCOORDINATOR_H

#include "qamflightinstrument.h"

class QamTurnCoordinator : public QamFlightInstrument
{
	Q_OBJECT

  public:
	explicit QamTurnCoordinator(QWidget* parent = 0 ) ;

  protected:
  	virtual void setDrawingArea(QPainter& painter ) ;
	virtual void drawBackground(QPainter& painter ) ;
	virtual void drawForeground(QPainter& painter ) ;
} ;

#endif
