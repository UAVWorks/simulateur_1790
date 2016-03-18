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
	int QFI_id;
	int QFI_axis;
	int addr_modip ;

public:
	Dataref(int freq, int id, QString* path, int QFI_id, int QFI_axis){}
	Dataref(int freq, int id, QString* path, int addr_modip) ;
	Dataref(float value, QString* path, int addr_modip) ;
	QString *getDatagram() ;

} ;

#endif