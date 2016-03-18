#include "Dataref.h"

void Dataref::setDataref(int freq, int id, QString* path)
{
	this->dref_freq=freq ;
	this->dref_id=id ;
	this->dref_path = path ;
	this->datagram<<"RREF0"<<freq<<id<<path<<'0' ;
}

void Dataref::setDataref(float value, QString* path)
{
	this->value=value ;
	this->dref_path=path ;
	this->datagram<<"DREF0"<<value<<path<<'0';
}
QString * Dataref::getDatagram()
{
	return this->datagram ;
}

