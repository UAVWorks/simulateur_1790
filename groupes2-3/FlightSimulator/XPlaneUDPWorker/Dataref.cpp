#include "Dataref.h"

Dataref::Dataref(const QString& path, int freq) {

}

Dataref::Dataref(int iId, int aId, bool input) {

}

Dataref::Dataref(const QString& input, const QString& output, float scale, float offset) {

}

bool Dataref::isRref() const {
	if (this->m_source=="RREF")
		return true ;
	return false ;
}

bool Dataref::isRrefQfi() const {
	if (this.isRref())
		if (this->m_target=="QFI")
			return true ;
	return false ;
}

bool Dataref::isRrefDigital() const {
	if (this.isRref())
		if (this->m_target=="TOR")
			return true ;
	return false ;
}

bool Dataref::isRrefAnalog() const {
	if (this.isRref())
		if (this->m_target=="ANA")
			return true ;
	return false ;
}

bool Dataref::Dref() const {
	if (this->m_target=="DREF")
		return true ;
	return false ;
}

bool Dataref::isDrefDigital() const {
	if (this.isDref())
		if (this->m_source=="TOR")
			return true ;
	return false ;
}

bool Dataref::isDrefAnalog() const {
	if (this.isDref())
		if (this->m_source=="ANA")
			return true ;
	return false ;
}

bool Dataref::isDigitalQfiInput() const {
	if (this->m_source=="TOR")
		if (this->m_target=="QFI")
			return true ;
	return false ;
}

bool Dataref::isAnalogQfiInput() const {
	if (this->m_source=="ANA")
		if (this->m_target=="QFI")
			return true ;
	return false ;
}

bool Dataref::isDigitalQfiOutput() const {
	if (this->m_source=="QFI")
		if (this->m_target=="TOR")
			return true ;
	return false ;
}

bool Dataref::isDigitalToDigital() const {
	if (this->m_source=="TOR")
		if (this->m_target=="TOR")
			return true ;
	return false ;
}