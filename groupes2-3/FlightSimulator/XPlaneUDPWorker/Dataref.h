#ifndef DATAREF_H
#define DATAREF_H

class Dataref
{
private:
	int dref_freq ;
	int dref_id ;
	QString* dref_path ;
	float value ;
	QString * datagram ;


public:
	Datagram(){}
	QString* setDataref(int freq, int id, QString* path) ;
	QString* setDataref(float value, QString* path) ;
	QString *getDatagram() ;

} ;

#endif