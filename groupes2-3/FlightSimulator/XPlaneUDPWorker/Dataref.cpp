#include "Dataref.h"

void setup() {

// ALTIMETRE
struct dref_struct_in QAltimeter ;
QAltimeter.dref_freq=100;
QAltimeter.dref_id=1;
QAltimeter.dref_path=;

// ANENOMETRE
struct dref_struct_in QAirSpeed ;
QAirSpeed.dref_freq=100;
QAirSpeed.dref_id=2 ;
QAirSpeed.dref_path="sim/cockpit2/gauges/indicators/airspeed kts pilot";

// VARIOMETRE
struct dref_struct_in QVariometer ;
QVariometer.dref_freq=100;
QVariometer.dref_id=3;
QVariometer.dref_path= "sim/cockpit2/gauges/indicators/airspeed acceleration kts sec pilot";

// GYROSCOPE DIRECTIONNEL
struct dref_struct_in QGyro ;
QGyro.dref_freq=100 ;
QGyro.dref_id=4 ;
QGyro.dref_path="sim/cockpit2/gauges/indicators/compass heading deg mag";

// HORIZON ARTIFICIEL
struct dref_struct_in QHA ;
QHA.dref_freq=100 ;
QHA.dref_id=5 ;
QHA.dref_path="sim/cockpit2/gauges/actuators/artificial horizon adjust deg pilot" ;

// TURN COORDINATOR
struct dref_struct_in QTC ;
QTC.dref_freq=100 ;
QTC.dref_id=6 ;
QTC.dref_path="sim/cockpit2/gauges/indicators/slip deg" ;

}
