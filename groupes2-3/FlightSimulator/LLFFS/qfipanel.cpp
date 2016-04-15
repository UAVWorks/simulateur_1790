#include "qfipanel.h"

QFIPanel::QFIPanel(QWidget *parent) : QWidget(parent)
{
    //setupUi(this);
    title = "Lycée La Fayette - Flight Simulator - SM 2016" ;
    this->setWindowTitle(title) ;
    this->setGeometry(0,0,1440,900) ;
    this->setStyleSheet("background-color:black ;") ;
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->show() ;

}
