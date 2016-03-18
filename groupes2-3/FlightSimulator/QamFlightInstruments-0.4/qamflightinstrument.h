/*  ---------------------------------------------------------------------------
 *  filename    :   qamflightinstrument.h
 *  description :   INTERFACE de la classe QamFlightInstrument
 *
 *	project     :	Widgets "Flight Instrument"
 *  start date  :   octobre 2015
 *  ---------------------------------------------------------------------------
 *  Copyright 2015-2016 by Alain Menu   <alain.menu@ac-creteil.fr>
 *
 *  This file is part of "Qam Flight Instruments Widgets Library"
 *
 *  This program is free software ;  you can  redistribute it and/or  modify it
 *  under the terms of the  GNU General Public License as published by the Free
 *  Software Foundation ; either version 3 of the License, or  (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY ; without even the  implied  warranty  of  MERCHANTABILITY  or
 *  FITNESS FOR  A PARTICULAR PURPOSE. See the  GNU General Public License  for
 *  more details.
 *
 *	You should have  received  a copy of the  GNU General Public License  along
 *	with this program. If not, see <http://www.gnu.org/licenses/>.
 *  ---------------------------------------------------------------------------
 */

#ifndef QAMFLIGHTINSTRUMENT_H
#define QAMFLIGHTINSTRUMENT_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QPainter>
#include <cmath>

#include "_ABOUT"

/*!
  @file
  @brief Classe modèle "Instruments de vol"
 */

/*!
 @class QamFlightInstrument
 @brief Classe modèle "Instruments de vol".

La classe QamFlightInstrument sert de modèle de développement pour des instruments de vol
aéronautiques.
La classe QamFlightInstrument est dérivée de QWidget, un objet de classe dérivée peut ainsi être 
directement référencé par promotion au sein d'une interface Designer.

La spécialisation de QamFlightInstrument peut se résumer à surcharger deux méthodes protégées :
- drawBackground() qui assure le dessin des parties fixes de l’instruments (fond, graduations... ) ;
- drawForeground() qui dessine les parties mobiles (aiguille…).

L'aire de dessin est retournée par la méthode drawingRect() ; elle est toujours équivalente
à une grille virtuelle de 1000 x 1000 points. La méthode drawingRadius () fournit quant à elle
le rayon maximum de l'instrument, normalement égal à 500 points (la majorité des instruments de vol
sont circulaires...).
Cette géométrie carrée par défaut avec origine au centre peut être surclassée par surcharge de la 
méthode protégée setDrawingArea(). Cette dernière reçoit un objet QPainter pour lequel elle doit
impérativement fixer l'origine (méthode QPainter.translate()) et l'échelle (méthode QPainter::scale()).

La classe QamFlightInstrument prend en charge la gestion d’un maximum de 4 grandeurs réelles ; ces
grandeurs jouent le rôle de variables d'animation de l'instrument.

Chaque grandeur est définie par :
- un label d'identification facultatif ;
- une unité (pourcentage par défaut) ;
- une valeur minimale (0.0 par défaut) ;
- une valeur maximale (100.0 par défaut) ;
- un seuil bas (égal à la valeur minimale par défaut) ;
- un seuil haut (égal à la valeur maximale par défaut) ;
- et sa valeur instantanée (50.0 par défaut).

Les accesseurs des propriétés précédentes attendent tous un argument nommé axis qui représente 
la grandeur concernée (valeur 0...3). La première grandeur est utilisée lorsque cet argument n'est
pas spécifié.

QamFlightInstrument propose des ressources graphiques permettant de dessiner rapidement :
- un fond de base noir avec anneau effet relief ;
- un axe d'aiguilles repositionnable (par défaut au centre du widget) ;
- un arc coloré paramétrable ;
- une graduation de type "rounded rectangle" paramétrable ;
- une aiguille classique ;
- une chaine de caractères positionnée par son centre.

Accessoirement, QamFlightInstrument propose un sélecteur de valeur et un bouton-poussoir
superposables au dessin de l'instrument.
Ces éléments sont montrés/cachés par clic sur le bouton gauche de la souris sur l'aire de l'instrument ;
la grandeur modifiable via le sélecteur est définissable par setAdjustable() ; par défaut, aucune grandeur 
n'est associée à ce sélecteur.
Un appui sur le bouton-poussoir virtuel déclenche le slot selectPressed(0) qu'il convient de surdéfinir
pour agir sur le comportement de l'instrument.
 */

#define	QFI_NUMAXIS	4					// nombre d'axes
#define	QFI_GRID	1000				// résolution de la grille de dessin
#define QFI_RADIUS	( QFI_GRID / 2 )	// rayon de l'instrument

class QamFlightInstrument : public QWidget
{
	Q_OBJECT

  public:
	explicit QamFlightInstrument(QWidget* parent = 0 ) ;
	virtual ~QamFlightInstrument() ;

	static QString version() ;

	int id() const ;
	void setId(int id ) ;
	QString	className() const ;
	
	enum AlarmState { Off, On, SlowBlink, FastBlink } ;

	QString label(int axis = 0 ) const ;
	QString unit(int axis = 0 ) const ;
	float value(int axis = 0 ) const ;
	float minimum(int axis = 0 ) const ;
	float maximum(int axis = 0 ) const ;
	float lowThreshold(int axis = 0 ) const ;
	float highThreshold(int axis = 0 ) const ;

	void setLabel(const QString& label, int axis = 0 ) ;
	void setUnit(const QString& unit, int axis = -1 ) ;
	void setMinimum(float minimum, int axis = 0 ) ;
	void setMaximum(float maximum, int axis = 0 ) ;
	void setMinMax(float minimum, float maximum, int axis = 0 ) ;
	void setLowThreshold(float low, int axis = 0 ) ;
	void setHighThreshold(float high, int axis = 0 ) ;
	void setThresholds(float low, float high, int axis = 0 ) ;

	bool isLowLevel(int axis = 0 ) const ;
	bool isHighLevel(int axis = 0 ) const ;
	bool isNormalLevel(int axis = 0 ) const ;

	void setAdjustable(float step, int prec, int axis = 0 ) ;
	bool isAdjustable(int axis = 0 ) const ;
	void resetAdjustable() ;

	QRect drawingRect() const ;
	int drawingRadius() const ;

  signals:
	void lowLevel(int axis = 0 ) ;
	void normalLevel(int axis = 0 ) ;
	void highLevel(int axis = 0 ) ;
	void valueChanged(float value, int axis = 0  ) ;
//	void alarmState(int led1, int led2 ) ; 
	void alarmState(int id, int num, int state ) ;			// pour pilotage led externe (4 états possibles)

  public slots:
	void setValue(float value, int axis = 0 ) ;
	virtual void selectPressed(int num, bool longClic = false ) ;	// pour pilotage par BP externe
	virtual void adjustmentChanged(int num, float value ) ;			// pour pilotage par Adj externe

  private slots:
  	void spinBoxValueChanged( double value ) ;
  	void pbuSelectClicked() ;
  	
  protected:
	virtual void setDrawingArea(QPainter& painter ) ;
	virtual void drawBackground(QPainter& painter ) ;
	virtual void drawForeground(QPainter& painter ) ;
	void updateWithBackground() ;

	void qfiBackground(QPainter& painter, float ringRadius, float ringThickness = 0.0 ) ;
	void qfiAxis(QPainter& painter, float radius, const QPoint& center = QPoint() ) ;
	void qfiArc(QPainter& painter, const QColor& color, float radius, float start, float span, int penThickness ) ;
	void qfiMarker(QPainter& painter, const QColor& color, float extRadius, QSize size ) ;
	void qfiNeedle(QPainter& painter, const QColor& color, QVector<QPointF> profil, float rAxis, float rCw = 0.0, float sep = 0.0 ) ;
	void qfiText(QPainter& painter, const QFont& font, const QColor& color, const QPoint& center, const QString& s ) ;	

  private:
	virtual void paintEvent(QPaintEvent* pe ) ;
	virtual void resizeEvent(QResizeEvent* event ) ;
	virtual void mousePressEvent(QMouseEvent* event ) ;

  private:
  	int		m_id ;
  	
  protected:
  	QString	m_class ;
  	
  private:
	QString	m_label[QFI_NUMAXIS] ;
	QString	m_unit[QFI_NUMAXIS] ;
	float	m_value[QFI_NUMAXIS] ;
	float	m_minimum[QFI_NUMAXIS] ;
	float	m_maximum[QFI_NUMAXIS] ;
	float	m_lowThreshold[QFI_NUMAXIS] ;
	float	m_highThreshold[QFI_NUMAXIS] ;
	bool	m_adjustable[QFI_NUMAXIS] ;

	bool		m_redraw ;			// indique si le fond doit être redessiné
	QPixmap*	m_background ;		// image de fond

	QDoubleSpinBox*	m_spinBox ;
	QPushButton*	m_pbuSelect ;
} ;

#endif // QFLIGHTINSTRUMENT_H
