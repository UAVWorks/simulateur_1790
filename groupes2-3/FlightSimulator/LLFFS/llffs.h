#ifndef LLFFS_H
#define LLFFS_H

#include <MainDialog.h>
#include <TCPWorker.h>
#include <XPlaneUDPWorker.h>
#include <Dataref.h>
#include <QWidget>
#include <qamflightinstrument.h>

class LLFFS : public QMainWindow, private Ui::LLFFS
{
    Q_OBJECT

public:
    explicit LLFFS(QWidget *parent = 0);
    void loadConf(const QString& csv) ;
private:
    MainDialog * maindialog ;
    TCPWorker * tcpworker;
    QList<QFlightInstrument *> QFIList ;
    QList<Dataref *> QDataref ;
};

#endif // LLFFS_H
