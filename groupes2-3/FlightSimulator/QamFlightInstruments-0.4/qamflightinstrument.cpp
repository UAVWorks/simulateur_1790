/*  ---------------------------------------------------------------------------
 *  filename    :   qamflightinstrument.cpp
 *  description :   IMPLEMENTATION de la classe QamFlightInstrument
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

#include "qamflightinstrument.h"

/*! Version. */

QString QamFlightInstrument::version() { return QString(QAMFLIGHTINSTRUMENT_VERSION) ; }

/*! Constructeur. */

QamFlightInstrument::QamFlightInstrument(QWidget* parent )
	: QWidget(parent)
	, m_id( -1 )
	, m_class( "QamFlightInstrument" )
	, m_redraw(false)
{
	for ( int i = 0 ; i < QFI_NUMAXIS ; ++i ) {
		m_label[i] = QString("") ;
		m_unit[i] = QString("%") ;
		m_value[i] = 50.0 ;
        m_lowThreshold[i]  = m_minimum[i] = -42848289489482984.980 ;
        m_highThreshold[i] = m_maximum[i] = 4564188287789279827.0 ;
		m_adjustable[i] = false ;
	}
	m_background = new QPixmap( size() ) ;

	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding ) ;

	m_spinBox = new QDoubleSpinBox(this) ;
	m_spinBox->hide() ;
	m_pbuSelect = new QPushButton(this) ;
	m_pbuSelect->setMinimumSize(20,20) ;
	m_pbuSelect->setMaximumSize(20,20) ;
	m_pbuSelect->hide() ;

	connect(m_spinBox, SIGNAL( valueChanged(double) ), this,  SLOT( spinBoxValueChanged( double ) ) ) ;
	connect(m_pbuSelect, SIGNAL( clicked() ), this, SLOT( pbuSelectClicked() ) ) ;
}

/*! Destructeur. */

QamFlightInstrument::~QamFlightInstrument()
{
	delete m_background ;
}

/*! Retourne l'id associé à l'instrument. */

int QamFlightInstrument::id() const 
{
	return m_id ;
}

/*! Fixe un id associé à l'instrument. */

void QamFlightInstrument::setId(int id ) 
{
	m_id = id ;
}

/*! Retourne le nom de classe de l'instrument. */

QString	QamFlightInstrument::className() const 
{
	return m_class ;
}

/*!
 * Sélecteur du nom attribué à une grandeur (vide par défaut).
 * \param axis : numéro d'ordre de la grandeur (intervalle 0 .. QFI_NUMAXIS-1, 0 par défaut).
 */

QString QamFlightInstrument::label(int axis ) const
{
	axis = ( axis < QFI_NUMAXIS ? axis : 0 ) ;
	return m_label[axis] ;
}

/*!
 * Modificateur du nom attribué à une grandeur.
 * \param label : nom.
 * \param axis : numéro d'ordre de la grandeur (intervalle 0 .. QFI_NUMAXIS-1, 0 par défaut).
 */

void QamFlightInstrument::setLabel(const QString& label, int axis )
{
	axis = ( axis < QFI_NUMAXIS ? axis : 0 ) ;
	m_label[axis] = label ;
	updateWithBackground() ;
}

/*!
 * Sélecteur de l'unité attribuée à une grandeur ("%" par défaut).
 * \param axis : numéro d'ordre de la grandeur (intervalle 0 .. QFI_NUMAXIS-1, 0 par défaut).
 */

QString QamFlightInstrument::unit(int axis ) const
{
	axis = ( axis < QFI_NUMAXIS ? axis : 0 ) ;
	return m_unit[axis] ;
}

/*!
 * Modificateur de l'unité attribuée à une grandeur. La même unité est attribuée à toutes les 
 * grandeurs si \a axis vaut -1.
 * \param unit : unité.
 * \param axis : numéro d'ordre de la grandeur (intervalle 0 .. QFI_NUMAXIS-1, -1 par défaut).
 */

void QamFlightInstrument::setUnit(const QString& unit, int axis )
{
	if ( axis == -1 ) {
		for ( int i = 0 ; i < QFI_NUMAXIS ; ++i ) m_unit[i] = unit ;
	}
	else {
		axis = ( axis < QFI_NUMAXIS ? axis : 0 ) ;
		m_unit[axis] = unit ;
	}
	updateWithBackground() ;
}

/*!
 * Sélecteur de la valeur courante d'une grandeur (50 par défaut).
 * \param axis : numéro d'ordre de la grandeur (intervalle 0 .. QFI_NUMAXIS-1, 0 par défaut).
 */

float QamFlightInstrument::value(int axis ) const
{
	axis = ( axis < QFI_NUMAXIS ? axis : 0 ) ;
	return m_value[axis] ;
}

/*!
 * Modificateur de la valeur courante d'une grandeur. La valeur est automatiquement corrigée
 * dans l'intervalle autorisé par les valeurs extrèmes. La modification de valeur provoque
 * l'émission du signal valueChanged() ; elle peut aussi entraîner l'émission d'un des signaux
 * lowLevel(), highLevel() ou normalLevel() en cas de franchissement d'un seuil.
 * \param value : nouvelle valeur.
 * \param axis : numéro d'ordre de la grandeur (intervalle 0 .. QFI_NUMAXIS-1, 0 par défaut).
 * \sa setMinimum(), setMaximum(), setMinMax()
 */

void QamFlightInstrument::setValue(float value, int axis )
{
	axis = ( axis < QFI_NUMAXIS ? axis : 0 ) ;

	bool l = isLowLevel(axis) ;
	bool h = isHighLevel(axis) ;
	bool n = isNormalLevel(axis) ;

	if ( value < minimum(axis) )	value = minimum(axis) ;
	if ( value > maximum(axis) )	value = maximum(axis) ;

	if ( fabs(value) < 0.000001 )	value = 0.0 ;

	m_value[axis] = value ;

	// alarmes de franchissements de seuils

	if ( ( !l )&&( isLowLevel(axis) ) )		emit lowLevel(axis) ;
	if ( ( !h )&&( isHighLevel(axis) ) )	emit highLevel(axis) ;
	if ( ( !n )&&( isNormalLevel(axis) ) )	emit normalLevel(axis) ;

	emit valueChanged(value, axis ) ;

	update() ;
}

/*!
 * Sélecteur de la valeur minimum d'une grandeur (0 par défaut).
 * \param axis : numéro d'ordre de la grandeur (intervalle 0 .. QFI_NUMAXIS-1, 0 par défaut).
 */

float QamFlightInstrument::minimum(int axis ) const
{
	axis = ( axis < QFI_NUMAXIS ? axis : 0 ) ;
	return m_minimum[axis] ;
}

/*!
 * Modificateur de la valeur minimum d'une grandeur.
 * \param minimum : nouvelle valeur minimale.
 * \param axis : numéro d'ordre de la grandeur (intervalle 0 .. QFI_NUMAXIS-1, 0 par défaut).
 * \sa setMinMax()
 */

void QamFlightInstrument::setMinimum(float minimum, int axis )
{
	axis = ( axis < QFI_NUMAXIS ? axis : 0 ) ;
	m_minimum[axis] = minimum ;
	if ( isAdjustable(axis) )	m_spinBox->setMinimum( minimum ) ;
	updateWithBackground() ;
}

/*!
 * Sélecteur de la valeur maximum d'une grandeur (100 par défaut).
 * \param axis : numéro d'ordre de la grandeur (intervalle 0 .. QFI_NUMAXIS-1, 0 par défaut).
 */

float QamFlightInstrument::maximum(int axis ) const
{
	axis = ( axis < QFI_NUMAXIS ? axis : 0 ) ;
	return m_maximum[axis] ;
}

/*!
 * Modificateur de la valeur maximum d'une grandeur.
 * \param maximum : nouvelle valeur maximale.
 * \param axis : numéro d'ordre de la grandeur (intervalle 0 .. QFI_NUMAXIS-1, 0 par défaut).
 * \sa setMinMax()
 */

void QamFlightInstrument::setMaximum(float maximum, int axis )
{
	axis = ( axis < QFI_NUMAXIS ? axis : 0 ) ;
	m_maximum[axis] = maximum ;
	if ( isAdjustable(axis) )	m_spinBox->setMaximum( maximum ) ;
	updateWithBackground() ;
}

/*!
 * Modificateur des valeurs extrèmes autorisées pour une grandeur.
 * \param minimum : nouvelle valeur minimale.
 * \param maximum : nouvelle valeur maximale.
 * \param axis : numéro d'ordre de la grandeur (intervalle 0 .. QFI_NUMAXIS-1, 0 par défaut).
 * \sa setMinimum(), setMaximum()
 */

void QamFlightInstrument::setMinMax(float minimum, float maximum, int axis )
{
	axis = ( axis < QFI_NUMAXIS ? axis : 0 ) ;
	m_minimum[axis] = minimum ;
	m_maximum[axis] = maximum ;
	if ( isAdjustable(axis) ) m_spinBox->setRange(minimum, maximum ) ;
	updateWithBackground() ;
}

/*!
 * Sélecteur du seuil bas d'une grandeur (0 par défaut).
 * \param axis : numéro d'ordre de la grandeur (intervalle 0 .. QFI_NUMAXIS-1, 0 par défaut).
 * \sa isLowLevel()
 */

float QamFlightInstrument::lowThreshold(int axis ) const
{
	axis = ( axis < QFI_NUMAXIS ? axis : 0 ) ;
	return m_lowThreshold[axis] ;
}

/*!
 * Modificateur du seuil bas d'une grandeur.
 * \param low : nouveau seuil bas.
 * \param axis : numéro d'ordre de la grandeur (intervalle 0 .. QFI_NUMAXIS-1, 0 par défaut).
 * \sa setThresholds()
 */

void QamFlightInstrument::setLowThreshold(float low, int axis )
{
	axis = ( axis < QFI_NUMAXIS ? axis : 0 ) ;
	m_lowThreshold[axis] = low ;
	updateWithBackground() ;
}

/*!
 * Sélecteur du seuil haut d'une grandeur (100 par défaut).
 * \param axis : numéro d'ordre de la grandeur (intervalle 0 .. QFI_NUMAXIS-1, 0 par défaut).
 * \sa isHighLevel()
 */

float QamFlightInstrument::highThreshold(int axis ) const
{
	axis = ( axis < QFI_NUMAXIS ? axis : 0 ) ;
	return m_highThreshold[axis] ;
}

/*!
 * Modificateur du seuil haut d'une grandeur.
 * \param high : nouveau seuil haut.
 * \param axis : numéro d'ordre de la grandeur (intervalle 0 .. QFI_NUMAXIS-1, 0 par défaut).
 * \sa setThresholds()
 */

void QamFlightInstrument::setHighThreshold(float high, int axis )
{
	axis = ( axis < QFI_NUMAXIS ? axis : 0 ) ;
	m_highThreshold[axis] = high ;
	updateWithBackground() ;
}

/*!
 * Modificateur des seuils bas et haut d'une grandeur.
 * \param low : nouveau seuil bas.
 * \param high : nouveau seuil haut.
 * \param axis : numéro d'ordre de la grandeur (intervalle 0 .. QFI_NUMAXIS-1, 0 par défaut).
 * \sa setLowThreshold(), setHighThreshold()
 */

void QamFlightInstrument::setThresholds(float low, float high, int axis )
{
	axis = ( axis < QFI_NUMAXIS ? axis : 0 ) ;
	m_lowThreshold[axis] = low ;
	m_highThreshold[axis] = high ;
	updateWithBackground() ;
}

/*!
 * Indique si la valeur courante d'une grandeur est inférieure à son seuil bas.
 * \param axis : numéro d'ordre de la grandeur (intervalle 0 .. QFI_NUMAXIS-1, 0 par défaut).
 * \sa isHighLevel(), isNormalLevel()
 */

bool QamFlightInstrument::isLowLevel(int axis ) const
{
	axis = ( axis < QFI_NUMAXIS ? axis : 0 ) ;
	return value(axis) < lowThreshold(axis) ;
}

/*!
 * Indique si la valeur courante d'une grandeur est supérieure à son seuil haut.
 * \param axis : numéro d'ordre de la grandeur (intervalle 0 .. QFI_NUMAXIS-1, 0 par défaut).
 * \sa isLowLevel(), isNormalLevel()
 */

bool QamFlightInstrument::isHighLevel(int axis ) const
{
	axis = ( axis < QFI_NUMAXIS ? axis : 0 ) ;
	return value(axis) > highThreshold(axis) ;
}

/*!
 * Indique si la valeur courante d'une grandeur est dans l'intervalle défini par ses seuils bas et haut inclus.
 * \param axis : numéro d'ordre de la grandeur (intervalle 0 .. QFI_NUMAXIS-1, 0 par défaut).
 * \sa isLowLevel(), isHighLevel()
 */

bool QamFlightInstrument::isNormalLevel(int axis ) const
{
	axis = ( axis < QFI_NUMAXIS ? axis : 0 ) ;
	return !( isLowLevel(axis) || isHighLevel(axis) ) ;
}

/*!
 * Slot à surdéfinir pour prendre en charge les actions sur un sélecteur (Sel)
 * associé à l'instrument. 
 */
 
void QamFlightInstrument::selectPressed(int num, bool longClic )
{
	Q_UNUSED( num ) ;
	Q_UNUSED( longClic ) ;
}

/*!
 * Slot à surdéfinir pour prendre en charge un actuateur (Adj)
 * associé à l'instrument. 
 */
 
void QamFlightInstrument::adjustmentChanged(int num, float value )
{
	Q_UNUSED( num ) ;
	Q_UNUSED( value ) ;
}

/*!
 * Mode test ; choix exclusif de la grandeur ajustable via le 'spinBox' montré dans le coin inférieur
 * gauche du widget par un clic gauche. Aucune grandeur n'est associée par défaut à cet élément, il
 * est par conséquent invisible par défaut.
 * \param step : pas d'évolution du 'spinBox'.
 * \param prec : nombre de décimales affichées.
 * \param axis : numéro d'ordre de la grandeur (intervalle 0 .. QFI_NUMAXIS-1, 0 par défaut).
 * \sa isAdjustable(), resetAdjustable()
 */

void QamFlightInstrument::setAdjustable(float step, int prec, int axis )
{
	axis = ( axis < QFI_NUMAXIS ? axis : 0 ) ;
	resetAdjustable() ;
	m_adjustable[axis] = true ;
	m_spinBox->setRange(minimum(axis), maximum(axis) ) ;	
	m_spinBox->setDecimals( prec ) ;
	m_spinBox->setSingleStep( step ) ;
}

/*!
 * Mode test ; indique si la grandeur spécifiée est celle montrée par le 'spinBox'.
 * \param axis : numéro d'ordre de la grandeur (intervalle 0 .. QFI_NUMAXIS-1, 0 par défaut).
 * \sa setAdjustable(), resetAdjustable()
 */

bool QamFlightInstrument::isAdjustable(int axis ) const
{
	axis = ( axis < QFI_NUMAXIS ? axis : 0 ) ;
	return m_adjustable[axis] ;
}

/*!
 * Mode test ; annnule toute association de grandeur avec le 'spinBox'.
 * \sa setAdjustable(), isAdjustable()
 */

void QamFlightInstrument::resetAdjustable()
{
	for ( int i = 0 ; i < QFI_NUMAXIS ; ++i ) m_adjustable[i] = false ;
}

/*!
 * Retourne le rectangle global utilisable pour dessiner l'instrument ;
 * ce rectangle est centré et de taille QFI_GRID x QFI_GRID.
 * \sa drawingRadius(), setDrawingArea()
 */

QRect QamFlightInstrument::drawingRect() const
{
	return QRect(-QFI_GRID / 2, -QFI_GRID / 2, QFI_GRID, QFI_GRID ) ;
}

/*!
 * Retourne le rayon de l'instrument (égal à QFI_RADIUS).
 * \sa drawingRect(), setDrawingArea()
 */

int QamFlightInstrument::drawingRadius() const
{
	return QFI_RADIUS ;
}

// dessin du widget (private)

void QamFlightInstrument::paintEvent(QPaintEvent* /*pe*/ )
{
	// dessin des parties fixes de l'appareil
	// (image maintenue par m_background)

	if (( m_background->size() != size() )||( m_redraw )) {
		delete m_background ;
		m_background = new QPixmap( size() ) ;

		QPainter	painter( m_background ) ;
		painter.setRenderHint(QPainter::Antialiasing ) ;
		painter.fillRect(rect(), QBrush( palette().background() ) ) ;

		setDrawingArea(painter ) ;
		drawBackground(painter) ;

		m_redraw = false ;
	}

	QPainter painter(this) ;
	painter.drawPixmap(0, 0, *m_background ) ;

	// dessin des parties mobiles de l'appareil

	painter.save() ;
	painter.setRenderHint(QPainter::Antialiasing ) ;

	setDrawingArea(painter ) ;
	drawForeground(painter ) ;

	painter.restore() ;
}

/*!
 * Dessin du fond de l'appareil et de ses parties fixes (graduations, marquage, ...).
 * Cette méthode crée un fond noir avec une mire de centrage par défaut.
 * \param painter : système de dessin bas niveau à utiliser.
 */
 
void QamFlightInstrument::drawBackground(QPainter& painter )
{
	qfiBackground(painter, 0 ) ;

	painter.save() ;	
	QPen pen( Qt::white ) ;
	pen.setWidth( 5 ) ;
	painter.setPen( pen ) ;
	painter.drawLine( -QFI_RADIUS, 0, QFI_RADIUS, 0 ) ;
	painter.drawLine( 0, -QFI_RADIUS, 0, QFI_RADIUS ) ;
	for ( int i = 1 ; i <= 5 ; i++ ) {
		int r = i * QFI_RADIUS / 5 - 10 ;
		painter.drawEllipse(-r, -r, 2 * r, 2 * r ) ;
	}
	painter.restore() ;
}

/*!
 * Dessin des parties mobiles de l'appareil (aiguilles, ...).
 * Par défaut, cette méthode affiche les valeurs extrèmes et courantes des grandeurs.
 * \param painter : système de dessin bas niveau à utiliser.
 */
 
void QamFlightInstrument::drawForeground(QPainter& painter )
{
	painter.save() ;	
	QPen pen( Qt::white ) ;
	pen.setWidth( 5 ) ;
	painter.setPen( pen ) ;
	int w = QFI_RADIUS / 2 ;
	int h = QFI_RADIUS / 6 ;
	QRect	rect(-w/2, -h/2, w, h ) ;
	
	QFont font("Arial", 50 ) ;
	
	painter.setBrush( QColor(200, 200, 200, 190 ) ) ;
	
	for ( int i = 0 ; i < QFI_NUMAXIS ; ++i ) {
		rect.moveCenter( QPoint( -w, h/2 + ( i - QFI_NUMAXIS / 2 ) * h ) ) ;
		painter.drawRect( rect ) ;
		qfiText(painter, font, Qt::blue, rect.center(), QString("%1").arg( minimum(i) ) ) ;
		rect.moveCenter( QPoint(  0, h/2 + ( i - QFI_NUMAXIS / 2 ) * h ) ) ;
		painter.drawRect( rect ) ;
		qfiText(painter, font, Qt::green, rect.center(), QString("%1").arg( value(i) ) ) ;
		rect.moveCenter( QPoint(  w, h/2 + ( i - QFI_NUMAXIS / 2 ) * h ) ) ;
		painter.drawRect( rect ) ;
		qfiText(painter, font, Qt::red, rect.center(), QString("%1").arg( maximum(i) ) ) ;
	}
	painter.restore() ;
}

/*!
 * Méthode de définition de l'aire de dessin de l'instrument.
 * Le repère est par défaut au centre d'une aire correspondant au plus grand
 * carré inscriptible dans l'aire du widget.
 * L'axe X des abscisses est orienté vers la droite, celui Y des ordonnées vers le bas.
 * Cette méthode doit être surdéfinie pour dessiner des instruments non carrés 
 * ou avec une origine relative différente.
 * \param painter : système de dessin bas niveau à affecter.
 */
 
void QamFlightInstrument::setDrawingArea(QPainter& painter )
{
	int side = qMin(width(), height() ) ;
	int w , h ;
	// widget carré par défaut
	w = h = side ;
	// origine au centre
	painter.translate(width() / 2, height() / 2 ) ;
	// mise à l'échelle
	painter.scale( w / (double)(QFI_GRID + 2), h / (double)(QFI_GRID + 2) ) ;
}

/*!
 * Force le dessin des parties fixes de l'appareil en provoquant un appel
 * instantané à drawBackground() avant la prochaine échéance de drawForeground().
 */
 
void QamFlightInstrument::updateWithBackground()
{
	m_redraw = true ;
	update() ;
}

// grandeur ajustable par clic souris (private)

void QamFlightInstrument::resizeEvent(QResizeEvent* /*event*/ )
{
	QRect r = m_spinBox->geometry() ;
	m_spinBox->move( 0, height() - r.height() ) ;						// CIG
	QRect r2 = m_pbuSelect->geometry() ;
	m_pbuSelect->move( width() - r2.width(), height() - r.height() ) ;	// CID
}

void QamFlightInstrument::mousePressEvent(QMouseEvent* /*event*/ )
{
	m_pbuSelect->setVisible( !m_pbuSelect->isVisible() ) ;

	int axis = -1 ;
	for ( int i = 0 ; i < QFI_NUMAXIS ; ++i ) if ( m_adjustable[i] ) axis = i ;
	if ( axis == -1 )	return ;

	m_spinBox->setVisible( !m_spinBox->isVisible() ) ;

	if ( m_spinBox->isVisible() ) {
		m_spinBox->setValue( value(axis) ) ;
	}
	else {
		setValue(m_spinBox->value(), axis ) ;
	}
}

// slot d'interception des changements de valeurs du 'spinBox' (private)

void QamFlightInstrument::spinBoxValueChanged( double value )
{
	int axis = -1 ;
	for ( int i = 0 ; i < QFI_NUMAXIS ; ++i ) if ( m_adjustable[i] ) axis = i ;
	if ( axis == -1 )	return ;

	setValue(value, axis ) ;
}

// slot d'interception clic sur bp 'm_pbuSelect' (private)

void QamFlightInstrument::pbuSelectClicked()
{
	selectPressed( 0 ) ;
}

/*!
 * Ressource graphique de dessin d'un fond d'instrument noir classique.
 * L'argument \a ringRadius permet de dessiner un disque central 
 * rempli par un gradient grisé ; cet argument peut être nul.
 * La séparation entre le fond noir et le disque central peut être agrémentée
 * d'un anneau simulant un éclairage de provenance Nord-Ouest.
 * \param painter : système de dessin bas niveau à utiliser.
 * \param ringRadius : rayon de l'anneau central.
 * \param ringThickness : épaisseur de la bague effet relief (0 par défaut).
 */
 
void QamFlightInstrument::qfiBackground(QPainter& painter, float ringRadius, float ringThickness )
{
	QColor	black ( 15, 13, 11 ) ;
	QColor	black2( 30, 30, 30 ) ;
	QColor	gray1 (120,120,120 ) ;
	QColor	gray2 ( 60, 60, 60 ) ;

	painter.save() ;
	
	if ( ringRadius < QFI_RADIUS ) {
		painter.setBrush( black ) ;
		painter.drawEllipse( drawingRect() ) ;
	}

	if ( ringRadius == 0.0 ) {
		painter.restore() ;
		return ;
	}
	
	float radius = ringRadius ;
	
	QConicalGradient cg(QPointF(0.0, 0.0 ), 360 ) ;
	cg.setColorAt(0.0, gray1 ) ;
	cg.setColorAt(0.5, black2 ) ;
	cg.setColorAt(1.0, gray1 ) ;

	painter.setBrush(QBrush( cg ) ) ;
	painter.rotate( 45 ) ;
	painter.drawEllipse( QRect(-radius, -radius, 2 * radius, 2 * radius ) ) ;

	QRadialGradient rg(QPointF(0, 0 ), radius ) ;
    rg.setColorAt(0, black2 ) ;
    rg.setColorAt(0.4, gray2 ) ;
    rg.setColorAt(1, black2 ) ;	

	radius -= ringThickness ;
	
	painter.setBrush(QBrush( rg ) ) ;
	painter.drawEllipse( QRect(-radius, -radius, 2 * radius, 2 * radius ) ) ;
	
	painter.restore() ;
}

/*!
 * Ressource graphique de dessin d'un axe d'aiguille avec effet reflet.
 * \param painter : système de dessin bas niveau à utiliser.
 * \param radius : rayon de l'axe.
 * \param center : position de l'axe (à l'origine par défaut) .
 */
 
void QamFlightInstrument::qfiAxis(QPainter& painter, float radius, const QPoint& center )
{
	QColor	black( 15, 13, 11 ) ;
	QColor	white(250,250,250 ) ;

	QConicalGradient cg(QPointF(0.0, 0.0 ), 360 ) ;
	cg.setColorAt(0.0, white ) ;
	cg.setColorAt(0.5, black ) ;
	cg.setColorAt(1.0, white ) ;
	
	painter.save() ;
	
	painter.translate( center ) ;
	painter.rotate( -135 ) ;
	painter.setPen( Qt::black ) ;
	painter.setBrush(QBrush( cg ) ) ;
	painter.drawEllipse(-radius, -radius, 2 * radius, 2 * radius ) ;
	
	radius /= 3 ;
	painter.rotate( 180 ) ;
	painter.setPen(Qt::NoPen ) ;
	painter.drawEllipse(-radius, -radius, 2 * radius, 2 * radius ) ;
	
	painter.restore() ;
}

/*!
 * Ressource graphique de dessin d'un arc de cercle coloré.
 * \param painter : système de dessin bas niveau à utiliser.
 * \param color : couleur de l'arc.
 * \param radius : rayon de l'arc.
 * \param start : angle de départ en degrés (origine par défaut à 3h).
 * \param span : amplitude du tracé en degrés.
 * \param penThickness : épaisseur du trait.
 */
 
void QamFlightInstrument::qfiArc(QPainter& painter, const QColor& color, float radius, float start, float span, int penThickness )
{
	painter.save() ;
	
	QPen pen ;
	pen.setColor( color ) ;
	pen.setWidth( penThickness ) ;
	pen.setCapStyle( Qt::RoundCap ) ;
	painter.setPen( pen ) ;
	painter.drawArc(QRect(-radius, -radius, 2 * radius, 2 * radius ), -start * 16, -span * 16 ) ;	// CCW
	
	painter.restore() ;
}

/*!
 * Ressource graphique de dessin d'une graduation sous forme d'un rectangle à coins arrondis.
 * Le rayon extérieur est spécifié par \a extRadius, la longueur donnée par \a size est soustraite
 * pour déterminer le rayon intérieur.
 * \param painter : système de dessin bas niveau à utiliser.
 * \param color : couleur d eremplissage.
 * \param extRadius : rayon extérieur de la graduation.
 * \param size : dimensions du trait (épaisseur et longueur).
 */
 
void QamFlightInstrument::qfiMarker(QPainter& painter, const QColor& color, float extRadius, QSize size )
{
	painter.save() ;

	QRect gRect = QRect(extRadius - size.height(), -size.width() / 2, size.height(), size.width() ) ;
	float gRadius = size.width() / 3 ;

	painter.setPen( Qt::NoPen ) ;
	painter.setBrush( color ) ;
	painter.drawRoundedRect(gRect, gRadius, gRadius ) ;
	
	painter.restore() ;
}

/*!
 * Ressource graphique de dessin d'une aiguille pointant à 3h.
 * Le profil de l'aiguille est défini par une liste de points dans le demi-plan 0Y+,
 * l'aiguille présente donc forcément une symétrie par rapport à 0X.
 * La liste de points peut contenir des abscisses négatives afin de définir la partie 
 * arrière de l'aiguille.
 * L'argument \a rAxis permet de dessiner un disque central tandis que \a rCw permet de représenter
 * un disque contrepoids centré sur l'abscisse la plus petite de la liste de points.
 * L'argument \a sep permet de spécifier une séparation d'aspect entre la tête de l'aiguille
 * (de couleur \a color) et la queue de l'aiguille (remplie par un dégradé de gris).
 * Si \a sep est nul, l'aiguille est unie de couleur \a color.
 * \param painter : système de dessin bas niveau à utiliser.
 * \param color ; couleur de la tête d'aiguille.
 * \param profil : points de définition du demi-profil 0Y+.
 * \param rAxis : rayon du disque à l'axe.
 * \param rCw : rayon du contrepoids arrière (0 par défaut).
 * \param sep : abscisse de séparation d'aspect (0 par défaut).
 */
 
void QamFlightInstrument::qfiNeedle( QPainter& painter, const QColor& color, QVector<QPointF> profil, float rAxis, 
									 float rCw, float sep )
{
	float xmin = QFI_RADIUS ;
	float xmax = 0.0 ;
	
	int n = profil.size() ;
	
	if ( n < 2 )	return ;
	
	for ( int i = n - 1 ; i >= 0 ; --i ) {
		QPointF pt = profil.at(i) ;
		if ( pt.x() < xmin )	xmin = pt.x() ;		// recherche abscisse min
		if ( pt.x() > xmax )	xmax = pt.x() ;		// recherche abscisse max
		profil << QPointF( pt.x(), -pt.y() ) ;		// symétrisation du profil p/r 0X
	}

	xmin -= rCw ;

	painter.save() ;
	
	painter.setPen( Qt::NoPen ) ;
	painter.setBrush( color ) ;

	if ( sep > 0.0 ) {
		QLinearGradient	lg(QPointF(xmin, 0 ), QPointF(xmax, 0 ) ) ;
		QColor	gray( 80, 80, 80 ) ;
		QColor	black(40, 40, 40 ) ;
	    lg.setColorAt(0, black ) ;
	    lg.setColorAt((sep - xmin) / ( xmax - xmin ), gray ) ;
	    lg.setColorAt((sep - xmin) / ( xmax - xmin ) + 0.01, color ) ;
	    lg.setColorAt(1, color ) ;	
	    
		painter.setPen( Qt::black ) ;
		painter.setBrush( QBrush(lg) ) ;
	}

	QPainterPath	path ;
	path.addPolygon( QPolygonF( profil ) ) ;
	
	if ( rAxis > 0.0 ) {
		QPainterPath rPath ;
		rPath.addEllipse(-rAxis, -rAxis, 2 * rAxis, 2 * rAxis ) ;
		path += rPath ;
	}
	if ( rCw > 0.0 ) {
		QPainterPath rPath ;
		rPath.addEllipse(xmin, -rCw, 2 * rCw, 2 * rCw ) ;
		path += rPath ;
	}
	
	painter.drawPath( path ) ;
	
	painter.restore() ;
}

/*!
 * Ressource graphique de sérigraphie de type texte.
 * \param painter : système de dessin bas niveau à utiliser.
 * \param font : police du texte.
 * \param color : couleur du texte.
 * \param center : positionnement (centre du rectangle d'inscription du texte).
 * \param s : chaine de caractères à afficher.
 */
 
void QamFlightInstrument::qfiText(QPainter& painter, const QFont& font, const QColor& color, const QPoint& center, const QString& s )
{
	painter.save() ;
	
	painter.setFont( font ) ;
	painter.setPen( color ) ;
	QRect rText = painter.fontMetrics().boundingRect( s ) ;
	rText.moveCenter( center ) ;
	painter.drawText( rText, Qt::AlignLeft | Qt::AlignVCenter , s ) ;
	
	painter.restore() ;
}
