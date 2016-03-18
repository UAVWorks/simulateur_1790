#ifndef DATAREF_H
#define DATAREF_H

class Dataref
{
private:
	int dref_freq ;
	int dref_id ;
	QString* dref_path ;

public:
	Dataref(int freq=100, int id, QString* path);

} ;

#endif