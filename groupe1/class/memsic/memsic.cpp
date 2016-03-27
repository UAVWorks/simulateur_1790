/**
 * \file	memsic.cpp
 * \author	calbatorix
 * \version 1.0
 * \date    26 mars 2016
 * \brief   Fichier de definition pour la class memsic.
 *
 * \details Ce fichier a pour but de definir les methodes et les constucteurs/destructeurs de la class memsic.
 *
 */
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

int memsic::value(int axes) const{
	memsic::update();

	if (axes == 1)
		return Valuex;
	if (axes == 2)
		return Valuey;
}
