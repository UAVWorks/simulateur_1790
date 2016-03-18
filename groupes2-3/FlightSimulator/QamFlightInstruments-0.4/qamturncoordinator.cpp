/*  ---------------------------------------------------------------------------
 *  filename    :   qamturncoordinator.cpp
 *  description :   IMPLEMENTATION de la classe QamTurnCoordinator
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

#include "qamturncoordinator.h"

QamTurnCoordinator::QamTurnCoordinator(QWidget* parent ) : QamFlightInstrument(parent)
{
	m_class = "QamTurnCoordinator" ;
}

void QamTurnCoordinator::setDrawingArea(QPainter& painter )
{
	painter.translate(width() / 2, height() / 2 ) ;
	painter.scale( width() / (double)(QFI_GRID + 2), height() / (double)(QFI_GRID + 2) ) ;
}

void QamTurnCoordinator::drawBackground(QPainter& painter )
{
	QamFlightInstrument::drawBackground(painter) ;
}

void QamTurnCoordinator::drawForeground(QPainter& painter )
{
}
