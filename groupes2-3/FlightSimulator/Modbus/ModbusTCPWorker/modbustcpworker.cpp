/*  ---------------------------------------------------------------------------
 *  filename    :   modbustcpworker.cpp
 *  description :   IMPLEMENTATION de la classe ModbusTcpWorker
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

#include "modbustcpworker.h"

ModbusTcpWorker::ModbusTcpWorker(QObject* parent )
	: QObject( parent )
{
}

// prise en charge d'un nouveau serveur

QamModbusMap* ModbusTcpWorker::addModbusSlave(const QString& configFile )
{
	QamModbusMap* map = new QamModbusMap(QamModbusMap::ClientMode, this ) ;
	QamTcpClient* client = new QamTcpClient(map, this ) ;



	connect( map, SIGNAL(info(QString,QString)), this, SIGNAL(modbusMapInfo(QString,QString)) ) ;

	emit modbusMapInfo("config", "new Modbus TCP/IP server" ) ;

	map->loadMap( configFile ) ;
	
	m_modbusMap << map ;
	m_tcpCLient << client ;

	return map ;
}

// slot dispatcher de commandes relatives à l'esclave n° 'slaveIndex'

void ModbusTcpWorker::slaveCommand(int slaveIndex, int cmd )
{
	switch( (SlaveCmd)cmd ) {
		case CONNECT :	connectToSlave( slaveIndex ) ;	break ;
		case RESET :	resetSlaveMap( slaveIndex ) ;	break ;
		case UPDATE :	updateSlaveMap( slaveIndex ) ;	break ;
		case REMOVE :	removeSlave( slaveIndex) ; 		break ;
	}
}

// mise à jour ponctuelle d'une entrée de la cartographie de l'esclave n° 'slaveIndex'

void ModbusTcpWorker::updateSlaveItem(int slaveIndex, int table, const QString& name )
{
	m_modbusMap.at( slaveIndex )->remoteValue( (QamModbusMap::PrimaryTable)table, name ) ;
}

// (private)
// suppression d'un esclave enregistré

void ModbusTcpWorker::removeSlave(int slaveIndex )
{
	bool connected = m_tcpCLient.at( slaveIndex )->state() == QAbstractSocket::ConnectedState ;
	if ( connected ) m_tcpCLient.at( slaveIndex )->sockClose() ;

	m_tcpCLient.removeAt( slaveIndex ) ;
	m_modbusMap.removeAt( slaveIndex ) ;
}

// (private)
// demande de connexion/déconnexion au serveur n° 'slaveIndex'

void ModbusTcpWorker::connectToSlave(int slaveIndex )
{
	bool connected = m_tcpCLient.at( slaveIndex )->state() == QAbstractSocket::ConnectedState ;
	QString host = m_modbusMap.at( slaveIndex )->host() ;
	quint16 port = m_modbusMap.at( slaveIndex )->port() ;
	
	if ( connected ) {
		m_tcpCLient.at( slaveIndex )->sockClose() ;
		emit connectChanged(slaveIndex, false ) ;
		return ;
	}
	else {
		emit modbusMapInfo("tcp/ip", QString("Connection to %1:%2...").arg(host).arg(port) ) ;
		m_tcpCLient.at( slaveIndex )->sockConnect(host, port ) ;
	
		if ( m_tcpCLient.at( slaveIndex )->waitForConnected(3000) ) {
			emit connectChanged(slaveIndex, true ) ;
			return ;	
		}
	}
	}

// (private)
// RAZ de toutes les valeurs (cartographie locale) du serveur 'slaveIndex'

void ModbusTcpWorker::resetSlaveMap(int slaveIndex )
{
	QamModbusMap::PrimaryTable	table ;

	table = QamModbusMap::Coil ;
	foreach(QString name, m_modbusMap.at( slaveIndex )->nameList( table ) ) {
		m_modbusMap.at( slaveIndex )->setLocalValue(table, name, "0" ) ;
	}
	table = QamModbusMap::DiscretInput ;
	foreach(QString name, m_modbusMap.at( slaveIndex )->nameList( table ) ) {
		m_modbusMap.at( slaveIndex )->setLocalValue(table, name, "0" ) ;
	}
	table = QamModbusMap::InputRegister ;
	foreach(QString name, m_modbusMap.at( slaveIndex )->nameList( table ) ) {
		QString display = m_modbusMap.at( slaveIndex )->display(table, name ) ;
		QString value = "0" ;
		if ( display == "Ascii" )	value = "" ;
		if (( display == "Str8" )||( display == "Str16" ))		value = "" ;
		m_modbusMap.at( slaveIndex )->setLocalValue(table, name, value ) ;
	}
	table = QamModbusMap::HoldingRegister ;
	foreach(QString name, m_modbusMap.at( slaveIndex )->nameList( table ) ) {
		QString display = m_modbusMap.at( slaveIndex )->display(table, name ) ;
		QString value = "0" ;
		if ( display == "Ascii" )	value = "" ;
		if (( display == "Str8" )||( display == "Str16" ))		value = "" ;
		m_modbusMap.at( slaveIndex )->setLocalValue(table, name, value ) ;
	}
}

// (private)
// demande d'actualisation de toutes les données
// par interrogations du serveur n° 'slaveIndex'

void ModbusTcpWorker::updateSlaveMap(int slaveIndex )
{
	if ( m_tcpCLient.at( slaveIndex )->state() != QAbstractSocket::ConnectedState )	return ;
	
	QamModbusMap::PrimaryTable	table ;

	table = QamModbusMap::Coil ;
	foreach(QString name, m_modbusMap.at( slaveIndex )->nameList( table ) ) {
		m_modbusMap.at( slaveIndex )->remoteValue(table, name ) ;
	}
	table = QamModbusMap::DiscretInput ;
	foreach(QString name, m_modbusMap.at( slaveIndex )->nameList( table ) ) {
		m_modbusMap.at( slaveIndex )->remoteValue(table, name ) ;
	}
	table = QamModbusMap::InputRegister ;
	foreach(QString name, m_modbusMap.at( slaveIndex )->nameList( table ) ) {
		m_modbusMap.at( slaveIndex )->remoteValue(table, name ) ;
	}
	table = QamModbusMap::HoldingRegister ;
	foreach(QString name, m_modbusMap.at( slaveIndex )->nameList( table ) ) {
		m_modbusMap.at( slaveIndex )->remoteValue(table, name ) ;
	}
}

// demande de mise à jour de la variable Modbus 16 bits 'name'
// ( concerne 'Led' )

void ModbusTcpWorker::setRemoteValue(const QString& name, float value )
{
	QamModbusMap* sl = NULL ;			// quel esclave ?
	QamModbusMap::PrimaryTable table ;	// quelle table R/W ?

	for ( int i = 0 ; i < m_modbusMap.size() ; ++i ) {

		if ( m_tcpCLient.at(i)->state() != QAbstractSocket::ConnectedState )	continue ;

		sl = m_modbusMap.at(i) ;
		table = QamModbusMap::HoldingRegister ;
		
		if ( slaveFullList(i, table ).contains( name ) ) {
			sl->setRemoteValue(table, name, QString("%1").arg((quint16)value) ) ;
			return ;
		}
	}
}

// demande de valeur de la variable Modbus 16 bits primaire ou secondaire 'name'
// ( concerne 'Sel', 'Int', 'Inv' et 'Adj' )

float ModbusTcpWorker::remoteValue(const QString& name )
{
	QamModbusMap* sl = NULL ;			// quel esclave ?
	QamModbusMap::PrimaryTable table ;	// quelle table ?
	
	for ( int i = 0 ; i < m_modbusMap.size() ; ++i ) {

		if ( m_tcpCLient.at(i)->state() != QAbstractSocket::ConnectedState )	continue ;

		sl = m_modbusMap.at(i) ;
		table = QamModbusMap::HoldingRegister ;
		
		if ( slaveFullList(i, table ).contains( name ) ) {
			return sl->remoteValue(table, name ).toFloat() ;
		}
		
		table = QamModbusMap::InputRegister ;
		
		if ( slaveFullList(i, table ).contains( name ) ) {
			return sl->remoteValue(table, name ).toFloat() ;
		}
	}
	return 0 ;
}

// (private)
// liste des données primaires et secondaires de la table 'table' du serveur 'slaveIndex'

QStringList ModbusTcpWorker::slaveFullList(int slaveIndex, QamModbusMap::PrimaryTable table )
{
	QStringList	list ;
	QStringList primaryList ;
	
	primaryList = m_modbusMap.at( slaveIndex )->nameList(table ) ;
	for ( int prim = 0 ; prim < primaryList.size() ; ++prim ) {
		list << primaryList.at(prim) ;
		QStringList	secondaryList = m_modbusMap.at( slaveIndex )->itemList(table, primaryList.at(prim) ) ;
		list << secondaryList ;
	}
	return list ;
}
