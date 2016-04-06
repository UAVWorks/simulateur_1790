#ifndef CAPTEUR_H
#define CAPTEUR_H

#include <Capteur.h>

class Potar : public Capteur{
	public:
	   Potar(int pin){Pin = pin;}
	   virtual void init();
	   virtual int update();
	private:
	   void mapMinMax(int read);
	   int Min;
	   int Max;
	   int Value;
};

#endif
