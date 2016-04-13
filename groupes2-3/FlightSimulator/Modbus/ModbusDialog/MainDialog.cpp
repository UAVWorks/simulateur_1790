#include "MainDialog.h"
#include <QMessageBox>
#include <QFileDialog>

MainDialog::MainDialog(QWidget *parent) : QDialog(parent)
{
    setupUi(this);
    this->show();

}

void MainDialog::addSlave(QamModbusMap *map){
    QamModbusMapViewer* viewer = new QamModbusMapViewer( this ) ;
    viewer->setModbusMap( map ) ;
    m_modbusMapViewer << viewer ;

    int i = tabWidget->addTab(m_modbusMapViewer.last(), map->description()) ;
    //edtHost->setText( map->host() ) ;
    //edtPort->setText( QString("%1").arg( map->port() ) ) ;

    tabWidget->setCurrentIndex( i ) ;
}

