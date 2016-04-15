#-------------------------------------------------
#
# Project created by QtCreator 2016-03-11T13:58:38
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LLFFS
TEMPLATE = app

OBJECTS_DIR = .obj
UI_DIR = .uic

MBDIALOGPATH = ../Modbus/ModbusDialog
MBTCPWORKERPATH = ../Modbus/ModbusTCPWorker
XPLANEUDPPATH = ../LLF-FS-sources
INSTRUMENTSPATH = ../QamFlightInstruments-0.4

INCLUDEPATH += . $${MBDIALOGPATH} $${MBTCPWORKERPATH} $${XPLANEUDPPATH} $${INSTRUMENTSPATH}

SOURCES += main.cpp\
    llffs.cpp \
    qfipanel.cpp \
    $${MBDIALOGPATH}/MainDialog.cpp \
    $${MBDIALOGPATH}/qammodbusmapviewer.cpp \
    $${INSTRUMENTSPATH}/qamchronograph.cpp \
    $${INSTRUMENTSPATH}/qamflightinstrument.cpp \
    $${INSTRUMENTSPATH}/qamtachymeter.cpp \
    $${INSTRUMENTSPATH}/qamturncoordinator.cpp \
    $${INSTRUMENTSPATH}/qaltimeter.cpp \
    $${INSTRUMENTSPATH}/qvariometer.cpp \
    $${INSTRUMENTSPATH}/qairspeed.cpp \
    $${INSTRUMENTSPATH}/qamgyrodir.cpp  \
    $${XPLANEUDPPATH}/dataref.cpp \
    $${XPLANEUDPPATH}/qamudpsocket.cpp \
    $${XPLANEUDPPATH}/xplaneudpworker.cpp \
    $${MBTCPWORKERPATH}/qamabstractserver.cpp \
    $${MBTCPWORKERPATH}/qammodbusdata.cpp \
    $${MBTCPWORKERPATH}/qammodbusmap.cpp \
    $${MBTCPWORKERPATH}/qamtcpclient.cpp \
    $${MBTCPWORKERPATH}/modbustcpworker.cpp \
    $${MBTCPWORKERPATH}/qamtcpserver.cpp \
    $${MBTCPWORKERPATH}/qamtcpconnection.cpp \
    ../QamFlightInstruments-0.4/QHA.cpp

HEADERS  += llffs.h \
    qfipanel.h \
    $${MBDIALOGPATH}/MainDialog.h \
    $${MBDIALOGPATH}/qammodbusmapviewer.h \
    $${MBTCPWORKERPATH}/qamabstractserver.h \
    $${MBTCPWORKERPATH}/qammodbusdata.h \
    $${MBTCPWORKERPATH}/qammodbusmap.h \
    $${MBTCPWORKERPATH}/qamtcpclient.h \
    $${MBTCPWORKERPATH}/modbustcpworker.h \
    $${MBTCPWORKERPATH}/qamtcpserver.h \
    $${MBTCPWORKERPATH}/qamtcpconnection.h \
    $${INSTRUMENTSPATH}/qamchronograph.h \
    $${INSTRUMENTSPATH}/qamflightinstrument.h \
    $${INSTRUMENTSPATH}/qamtachymeter.h \
    $${INSTRUMENTSPATH}/qamturncoordinator.h \
    $${INSTRUMENTSPATH}/qaltimeter.h \
    $${INSTRUMENTSPATH}/qvariometer.h \
    $${INSTRUMENTSPATH}/qairspeed.h \
    $${INSTRUMENTSPATH}/qamgyrodir.h \
    $${XPLANEUDPPATH}/dataref.h \
    $${XPLANEUDPPATH}/qamudpsocket.h \
    $${XPLANEUDPPATH}/xplaneudpworker.h \
    ../QamFlightInstruments-0.4/QHA.h

FORMS    += \
    $${MBDIALOGPATH}/maindialog.ui
