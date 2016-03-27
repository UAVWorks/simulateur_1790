#include <potar.h>
#include <memsic.h>

potar 	collectif(0);
potar 	pallonier(1);
memsic 	cyclique(2,3);

void setup()
{
	Serial.begin(9600);
}

void loop(){
	Serial.print("collectif: ");
	Serial.println(collectif.value());
	Serial.print("pallonier: ");
	Serial.println(pallonier.value());
	Serial.print("cycliqueX: ");
	Serial.println(cyclique.value(1));
	Serial.print("cycliqueY: ");
	Serial.println(cyclique.value(2));
	delay(100);
}
