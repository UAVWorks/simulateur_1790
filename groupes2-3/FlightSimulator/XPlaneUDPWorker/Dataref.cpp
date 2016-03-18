#include "Dataref.h"


Dataref::Dataref (int freq=100, int id, QString* path)
{
	this->dref_freq=freq;
	this->dref_id=id;
	this->dref_path=path;
}
