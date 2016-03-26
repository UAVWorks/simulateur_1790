#include "potar.h"

potar::potar(int Pin){
	in = Pin;
	int read = analogRead(in);
	min = read;
	max = read+1;
}

void potar::update(){
	Valueanalog = analogRead(in);

    if ( Valeur < min)
    	min = Valeur ;
    if ( Valeur> max)
        max = Valeur ;
}

int potar::value(){
	potar::update();
	Value = map(Valueanalog,min,max,-32768,32767);
	return Value;
}
