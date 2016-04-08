#include "Dataref.h"

int Dataref::m_idProvider = 0 ;

// constructeur RREF

Dataref::Dataref(const QString& path, int freq)
{
    m_id = ++m_idProvider ;
	this->m_sourceName=path ;
	this->m_rrefFreq=freq ;
}

Dataref::Dataref(int iId, int aId, bool input)
{
    m_id = ++m_idProvider ;
    this->m_instrumentId=iId;
	this->m_instrumentAxis=aId;
}

Dataref::Dataref(const QString& input, const QString& output, float scale, float offset)
{
    m_id = ++m_idProvider ;
    this->m_sourceName =input ;
	this->m_targetName= output ;
	this->m_scale=scale;
	this->m_offset=offset;
}


void bindToInstrument(int iId, int aId, float scale, float offset) {

}

void bindToDigitalIo(const QString& name, float scale, float offset) {
	
}

void bindToAnalogIo(const QString& name, float scale, float offset) {

}

QByteArray Dataref::xplaneRrefRequest() const {
	QByteArray trame;
    trame.append("RREF", 4 ) ;
	trame.append((char)0);
	trame.append( (char*)(&m_rrefFreq), 4 );
	trame.append( (char*)(&m_id), 4 );
	
//	QString path("sim/cockpit2/gauges/indicators/altitude_ft_pilot") ;
    trame.append(m_sourceName) ;
    trame.append( QByteArray(400 - m_sourceName.size() , (char)0 ) ) ;
	return trame;
}

QByteArray Dataref::xplaneRrefStop() const {

}

QByteArray Dataref::xplaneDref(float value) const {

}


int Dataref::id() const {

}


QString Dataref::sourceName() const {

}

QString Dataref::targetName() const {

} 


int Dataref::instrumentId() const {

}

int Dataref::instrumentAxis() const {

}

float Dataref::scale() const {

}

float Dataref::offset() const {
	
}


float Dataref::lastValue() const {

}

void Dataref::setLastValue(float v) {

}


bool Dataref::isRref() const {
   /* if (this->m_source=="RREF")
		return true ;
    return false ;*/
}

bool Dataref::isRrefQfi() const {
    /*if (this.isRref())
		if (this->m_target=="QFI")
			return true ;
    return false ;*/
}

bool Dataref::isRrefDigital() const {
    /*if (this.isRref())
		if (this->m_target=="TOR")
			return true ;
    return false ;*/
}

bool Dataref::isRrefAnalog() const {
    /*if (this.isRref())
		if (this->m_target=="ANA")
			return true ;
    return false ;*/
}


bool Dataref::isDref() const {
    /*if (this->m_target=="DREF")
		return true ;
    return false ;*/
}

bool Dataref::isDrefDigital() const {
    /*if (this.isDref())
		if (this->m_source=="TOR")
			return true ;
    return false ;*/
}

bool Dataref::isDrefAnalog() const {
    /*if (this.isDref())
		if (this->m_source=="ANA")
			return true ;
    return false ;*/
}


bool Dataref::isDigitalQfiInput() const {
    /*if (this->m_source=="TOR")
		if (this->m_target=="QFI")
			return true ;
    return false ;*/
}

bool Dataref::isAnalogQfiInput() const {
    /*if (this->m_source=="ANA")
		if (this->m_target=="QFI")
			return true ;
    return false ;*/
}

bool Dataref::isDigitalQfiOutput() const {
    /*if (this->m_source=="QFI")
		if (this->m_target=="TOR")
			return true ;
    return false ;*/
}

bool Dataref::isDigitalToDigital() const {
    /*if (this->m_source=="TOR")
		if (this->m_target=="TOR")
			return true ;
    return false ;*/
}


float Dataref::scaled(float value) const {

}

QByteArray Dataref::xplaneRref(int freq) const {

}
