/**
 * \file	bouton.h
 * \author	calbatorix
 * \version 1.0
 * \date    26 mars 2016 
 * \brief   Creation de la class bouton.
 *
 * \details todo.
 *
 */
#ifndef BOUTON_H_
#define BOUTON_H_

#include <Arduino.h>

class bouton{
	public:
		/*!
     	*  \brief Constructeur
     	*
     	*  Constructeur de la classe bouton.
     	*
     	*  \param Pin : pin où est branché la sortie du bouton.
	    */
		bouton(int Pin);

		/*!
     	*  \brief lecture de l'etat du bouton.
     	*
     	*  Methode qui permet de recuperer l'etat du bouton a 
     	* transmetre au rapport du joystick.
     	*  \return l'etat du bouton.
     	*/
		int value();
	private:
		void update();
		int in;
		int Value;
};

#endif
