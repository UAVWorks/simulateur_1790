/**
 * \file    capteurs.h
 * \author	calbatorix
 * \version 1.0
 * \date    26 mars 2016
 * \brief   Creation d'une classe abstraite pour tout les capteurs.
 *
 * \details todo.
 *
 */
#ifndef CAPTEURS_H_
#define CAPTEURS_H_

#include <Arduino.h>

 class capteurs
 {
 public:
 	capteurs(int nom_commande);
 	virtual void update();
 	virtual int value() = 0 ;
 	
 };
