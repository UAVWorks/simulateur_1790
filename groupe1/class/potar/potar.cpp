/**
 * \file	potar.cpp
 * \author	calbatorix
 * \version 1.0
 * \date    26 mars 2016
 * \brief   Fichier de definition pour la class potar.
 *
 * \details Ce fichier a pour but de definir les methodes et les constucteurs/destructeurs de la class potar.
 *
 */
#include "potar.h"

potar::potar(int Pin){
	in = Pin;
	int read = analogRead(in);
	min = read;
	max = read+1;
}

void potar::update(){
	Valueanalog = analogRead(in);

    if ( Value < min)
    	min = Value ;
    if ( Value> max)
        max = Value ;
	Value = map(Valueanalog,min,max,-32768,32767);
}

int potar::value() {
	potar::update();
	return Value;
}
