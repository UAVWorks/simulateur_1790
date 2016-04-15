/*  ---------------------------------------------------------------------------
 *  filename    :   modbustcpworker.h
 *  description :   INTERFACE de la classe ModbusTcpWorker
 *
 *	project     :	FlightSim
 *  start date  :   février 2016
 *  ---------------------------------------------------------------------------
 *  Copyright 2016 by Alain Menu   <alain.menu@ac-creteil.fr>
 *
 *  This file is part of "LLF Flight Simulator Project"
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

#ifndef MODBUSTCPWORKER_H
#define MODBUSTCPWORKER_H

//	Classe d'interface entre FlightSim et les esclaves Modbus/IP
// ---------------------------------------------------------------------------
// - [dé]référencement des serveurs
// - [dé]connexion avec les serveurs
// - lecture/écriture de données
// - remontée des messages en provenance de QamModbusMap/QamTcpClient
// ---------------------------------------------------------------------------

#include <QObject>
#include <qamtcpclient.h>
#include <qamtcpserver.h>
#include <qammodbusmap.h>

class ModbusTcpWorker : public QObject
{
	Q_OBJECT

  public:
  	explicit ModbusTcpWorker(QObject* parent = 0 ) ;
  	
  	QamModbusMap* addModbusSlave(const QString& configFile ) ;
	
	void  setRemoteValue(const QString& name, float value ) ;
	float remoteValue(const QString& name ) ;
	
	enum SlaveCmd { CONNECT, RESET, UPDATE, REMOVE } ;

  public slots:
  	void slaveCommand(int slaveIndex, int cmd ) ;
  	void updateSlaveItem(int slaveIndex, int table, const QString& name ) ;
  	
  private:
	void connectToSlave(int slaveIndex ) ;
  	void removeSlave(int slaveIndex ) ;
	void resetSlaveMap(int slaveIndex ) ;
	void updateSlaveMap(int slaveIndex ) ;

  signals:
	void connectChanged(int slaveIndex, bool connected ) ;
	void modbusMapInfo(QString, QString ) ;
	
  private:
  	QStringList	slaveFullList(int slaveIndex, QamModbusMap::PrimaryTable table ) ;

  private:
	QList<QamModbusMap*>	m_modbusMap ;
	QList<QamTcpClient*>	m_tcpCLient ;
} ;

#endif
