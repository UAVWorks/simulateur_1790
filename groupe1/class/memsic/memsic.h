#ifndef MEMSIC_H_
#define MEMSIC_H_

#include <Arduino.h>

class memsic{
	public:
		memsic(int Pinx, int Piny);
		int value(char sortie);
		
	private:
		void update();
		int inx;
		int iny
		int pulsex;
		int pulsey;
		int Valuex;
		int Valuey;
		int minx;
		int maxx;
		int miny;
		int maxy;
};

#endif