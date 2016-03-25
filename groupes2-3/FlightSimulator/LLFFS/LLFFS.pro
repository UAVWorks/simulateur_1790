#-------------------------------------------------
#
# Project created by QtCreator 2016-03-11T13:58:38
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LLFFS
TEMPLATE = app


MBDIALOGPATH = ../Modbus/ModbusDialog
MBTCPWORKERPATH = ../Modbus/ModbusTCPWorker
XPLANEUDPPATH = ../XPlaneUDPWorker
INSTRUMENTSPATH = ../QamFlightInstruments-0.4

INCLUDEPATH += . $${MBDIALOGPATH} $${MBTCPWORKERPATH} $${XPLANEUDPPATH} $${INSTRUMENTSPATH}

SOURCES += main.cpp\
        llffs.cpp \
    $${MBDIALOGPATH}/MainDialog.cpp \
    $${MBDIALOGPATH}/qammodbusmapviewer.cpp \
    $${MBTCPWORKERPATH}/qamabstractserver.cpp \
    $${MBTCPWORKERPATH}/qammodbusdata.cpp \
    $${MBTCPWORKERPATH}/qammodbusmap.cpp \
    $${MBTCPWORKERPATH}/qamtcpclient.cpp \
    $${MBTCPWORKERPATH}/TCPWorker.cpp \
    $${XPLANEUDPPATH}/Dataref.cpp \
    $${XPLANEUDPPATH}/XPlaneUDPWorker.cpp \
    $${INSTRUMENTSPATH}/qamchronograph.cpp \
    $${INSTRUMENTSPATH}/qamflightinstrument.cpp \
    $${INSTRUMENTSPATH}/qamtachymeter.cpp \
    $${INSTRUMENTSPATH}/qamturncoordinator.cpp \
    $${INSTRUMENTSPATH}/qaltimeter.cpp \
    $${INSTRUMENTSPATH}/qvariometer.cpp \
    $${INSTRUMENTSPATH}/qairspeed.cpp \
    llffs.cpp

HEADERS  += llffs.h \
    $${MBDIALOGPATH}/MainDialog.h \
    $${MBDIALOGPATH}/qammodbusmapviewer.h \
    $${MBTCPWORKERPATH}/qamabstractserver.h \
    $${MBTCPWORKERPATH}/qammodbusdata.h \
    $${MBTCPWORKERPATH}/qammodbusmap.h \
    $${MBTCPWORKERPATH}/qamtcpclient.h \
    $${MBTCPWORKERPATH}/TCPWorker.h \
    $${XPLANEUDPPATH}/Dataref.h \
    $${XPLANEUDPPATH}/XPlaneUDPWorker.h \
    $${INSTRUMENTSPATH}/qamchronograph.h \
    $${INSTRUMENTSPATH}/qamflightinstrument.h \
    $${INSTRUMENTSPATH}/qamtachymeter.h \
    $${INSTRUMENTSPATH}/qamturncoordinator.h \
    $${INSTRUMENTSPATH}/qaltimeter.h \
    $${INSTRUMENTSPATH}/qvariometer.h \
    $${INSTRUMENTSPATH}/qairspeed.h

FORMS    += \
    $${MBDIALOGPATH}/maindialog.ui \
    llffs.ui
