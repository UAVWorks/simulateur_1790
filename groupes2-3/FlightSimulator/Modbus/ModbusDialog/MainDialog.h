#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include "ui_maindialog.h"
#include <QCloseEvent>
#include "qammodbusmapviewer.h"
#include <qammodbusmap.h>
#include <qamtcpclient.h>

class MainDialog : public QDialog, private Ui::MainDialog
{
      Q_OBJECT

public:
    explicit MainDialog(QWidget* parent = 0) ;
    void addSlave(QamModbusMap* map) ;

signals :
    //void close() ;

private:
    
    QList<QamModbusMapViewer *> m_modbusMapViewer ;

};


#endif
