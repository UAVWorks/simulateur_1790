#ifndef BOUTON_H_
#define BOUTON_H_

#include <Arduino.h>

class bouton{
	public:
		bouton(int Pin);
		int value();
	private:
		void update();
		int in;
		int Value;
};

#endif
