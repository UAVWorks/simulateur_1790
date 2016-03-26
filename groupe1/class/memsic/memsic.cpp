#include "memsic.h"

memsic::memsic(int Pinx, int Piny){
	inx = Pinx;
	iny = Piny;
	int x = pulseIn(inx,HIGH);
	int y = pulseIn(iny,HIGH);
	minx = x;
	maxx = x+1;
	miny = y;
	maxy = y+1;
}

void memsic::update(){
	pulsex = pulseIn(inx,HIGH);
	pulsey = pulseIn(iny,HIGH);

	if( Valuex < minx)
		minx = Valuex;
	if (Valuex > maxx)
		maxx = Valuex;
	if( Valuey < miny)
		miny = Valuey;
	if (Valuey > maxx)
		maxy = Valuey;
	
	Valuex = map(pulsex,minx,maxx,-32768,32767);
	Valuey = map(pulsey,miny,maxy,-32768,32767);
}

int memsic::value(char sortie){
	memsic::update();

	if (sortie == "x")
		return Valuex;
	if (sorite == "y")
		return Valuey;
}