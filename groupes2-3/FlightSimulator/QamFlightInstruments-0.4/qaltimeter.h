#ifndef QALTIMETER_H
#define QALTIMETER_H

#include "qamflightinstrument.h"
#include <QTimer>
#include <QTime>
#include <QObject>
#include <QFont>


class QAltimeter : public QamFlightInstrument
{
    Q_OBJECT

  public:
    explicit QAltimeter(QWidget* parent = 0 ) ;
    void setDuration(int secs);
    int duration() const;
   // void draw(QPainter * painter);
    void drawText(const QPoint & position, const QString & text) ;

    enum Axis{ ALTIMETER, QNH } ;

  private slots:
//    void selectChanged() ;

  protected:
    virtual void drawBackground(QPainter& painter ) ;
    virtual void drawForeground(QPainter& painter ) ;

  private:
    void showArc(QPainter&, QColor&, float, float, float ) ;
    void showText(QPainter&, QFont&, QColor&, const QPoint&, const QString& ) ;

  private:
    QFont fo1;
    QFont fo2;
    QFont fo3;
    float	m_radius[2] ;	// rayon ext. graduation
    float	m_start[2] ;	// angle de l'origine (p/r 3 o'clock)
    float	m_span[2] ;		// amplitude angulaire totale
    float	m_step[2] ;		// pas des graduations
    float	m_min[2] ;		// graduation minimale
    float	m_max[2] ; 		// graduation maximale

} ;

#endif // QALTIMETER_H
