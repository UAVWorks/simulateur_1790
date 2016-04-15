#ifndef CAPTEUR_H
#define CAPTEUR_H

#include <Arduino.h>

class Capteur{
	public:
	   Capteur(int pin);
	   virtual void init() const = 0;
	   virtual int update() const = 0;
	protected:
	   int Pin;
};

#endif
