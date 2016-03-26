#include <potar.h>
#include <memsic.h>

potar 	collectif(0);
potar 	pallonier(1);
memsic 	cyclique(2,3);
char x = "x";
char y = "y";

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
	Serial.println(cyclique.value(x));
	Serial.print("cycliqueY: ");
	Serial.println(cyclique.value(y));
	delay(100);
}