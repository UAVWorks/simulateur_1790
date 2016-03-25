#ifndef DATAREF_H
#define DATAREF_H

#include <QString>
#include <QByteArray>

#define UNLIKELY_FLOAT 0.123456789

typedef struct 
{
	int id ;
	float value ;
} XPlaneRrefAnswer ;

class Dataref
{

public:

	//	Dataref(int freq, int id, QString* path, int QFI_id, int QFI_axis){}
	//	Dataref(int freq, int id, QString* path, int addr_modip) ;
	//	Dataref(float value, QString* path, int addr_modip) ;
	//	QString *getDatagram() ;

	Dataref(const QString& path, int freq= 0) ;
	Dataref(int iId, int aId, bool input = true) ;
	Dataref(const QString& input, const QString& output, float scale = 1, float offset = 0) ;

	void bindToInstrument(int iId, int aId, float scale = 1, float offset = 0 ) ;
	void bindToDigitalIo(const QString& name, float scale = 1, float offset = 0) ;
	void bindToAnalogIo(const QString& name, float scale = 1, float offset = 0 ) ;

	enum BindType { UNK, RREF, DREF, QFI, TOR, ANA } ;

	QByteArray xplaneRrefRequest() const ;
	QByteArray xplaneRrefStop() const ;
	QByteArray xplaneDref(float value) const ;

	int id() const ;

	QString sourceName() const ;
	QString targetName() const ;

	int instrumentId() const ;
	int instrumentAxis() const ;
	float scale() const ;
	float offset() const ;

	float lastValue() const ;
	void setLastValue(float v ) ;

	bool isRref() const ;				// RREF_*
	bool isRrefQfi() const ;			// RREF_QFI
	bool isRrefDigital() const ;		// RREF_TOR
	bool isRrefAnalog() const ;			// RREF_ANA

	bool isDref() const ;				//    *_DREF
	bool isDrefDigital() const ;		//  TOR_DREF
	bool isDrefAnalog() const ;			//  ANA_DREF

	bool isDigitalQfiInput() const ; 	//  TOR_QFI
	bool isAnalogQfiInput() const ;		//  ANA_QFI
	bool isDigitalQfiOutput() const ;	//	QFI_TOR
	bool isDigitalToDigital() const ;	//  TOR_TOR

	float scaled(float value) const ;

private:
	QByteArray xplaneRref(int freq = 0 ) const ;

private:
	//	int dref_freq ;
	//	int dref_id ;
	//	QString* dref_path ;
	//	float value ;
	//	QString * datagram ;
	//	int QFI_id;
	//	int QFI_axis;
	//	int addr_modip ;

	static int m_idProvider ;		// association id
	int m_id ;

	BindType m_source ;				// association source type
	BindType m_target ;				// association target type
	QString m_sourceName ;			// association source path or name
	Qtring m_targetName ;			// association target path or name

	float m_scale ;					// scale factor
	float m_offset ;				// zero offset
	float m_lastValue ;				// source current value memory

	int m_rrefFreq ;				// RREF number of request per second

	int m_instrumentId ;			// QFI id
	int m_instrumentAxis ;			// QFI axis or order number
	
} ;

#endif