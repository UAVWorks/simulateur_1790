/**
 * \file	memsic.h
 * \author	calbatorix
 * \version 1.0
 * \date    26 mars 2016
 * \brief   Creation de la class mesic.
 *
 * \details todo.
 *
 */
#ifndef MEMSIC_H_
#define MEMSIC_H_

#include <Arduino.h>

class memsic{
	public:
		/*!
     	*  \brief Constructeur
     	*
     	*  Constructeur de la classe memsic.
     	*
     	*  \param Pinx : pin où est branché la sortie Xout de l'accelerometre.
     	*  \param Piny : pin où est branché la sortie Yout de l'accelerometre.
	    */
		memsic(int Pinx, int Piny);
		/*!
     	*  \brief lecture de la valeur de l'accelerometre.
     	*
     	*  Methode qui permet de recuperer la valeur de sortie de l'accelerometre
     	* transmetre au rapport du joystick.
     	*  \param sortie : l'axe dont on veut recupere la valeur.
     	*  \return la valeur de l'axe choisi.
     	*/
		int value(int axes) ;

	private:
		void update();
		int inx;
		int iny;
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
