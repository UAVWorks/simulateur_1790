#ifndef POTAR_H_
#define POTAR_H_

#include <Arduino.h>

class potar{
	public:
		potar(int Pin);
		int value();
	private:
		void update();
		int in;
		int Valueanalog;
		int Value;
		int min;
		int max;
};

#endif