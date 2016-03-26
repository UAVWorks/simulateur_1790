#include "bouton.h"

bouton::bouton(int Pin){
	in = Pin;
	pinMode(in, INPUT);
	digitalWrite(in, 0);
}

void bouton::update(){
	Value = digitalRead(in);
}

int bouton::etat(){
	bouton::update();
	return Value ;
}
