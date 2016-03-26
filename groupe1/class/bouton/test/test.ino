#include <bouton.h>

bouton switch1(2);

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	Serial.println(switch1.etat());
delay(100);
}
