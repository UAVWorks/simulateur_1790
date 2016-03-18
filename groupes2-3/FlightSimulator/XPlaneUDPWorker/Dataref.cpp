#include "Dataref.h"

Dataref::Dataref(int freq, int id, QString* path, int QFI_id, int QFI_axis)
{
	this->dref_freq=freq ;
	this->dref_id=id ;
	this->dref_path = path ;
	this->QFI_id = QFI_id ;
	this->QFI_axis=QFI_axis ;
	this->datagram<<"RREF0"<<freq<<id<<path<<'0' ;
}

Dataref::Dataref(int freq, int id, QString* path, int addr_modip)
{
	this->value=value ;
	this->dref_path=path ;
	this->addr_modip=addr_modip ;
	this->datagram<<"RREF0"<<freq<<id<<path<<'0';
}

Dataref::Dataref(float value, QString* path, int addr_modip)
{
	this->value=value ;
	this->dref_path=path ;
	this->addr_modip=addr_modip;
	this->datagram<<"DREF0"<<value<<path<<'0';
}

QString * Dataref::getDatagram()
{
	return this->datagram ;
}

