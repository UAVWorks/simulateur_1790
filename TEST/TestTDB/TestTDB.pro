#-------------------------------------------------
#
# Project created by QtCreator 2016-03-29T10:15:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestTDB
TEMPLATE = app

QFIPATH = ../QamFlightInstruments-0.4
UDPPATH = ../LLF-FS-sources

INCLUDEPATH += . $${QFIPATH} $${UDPPATH}

SOURCES += main.cpp\
        test.cpp \
    $${QFIPATH}/qairspeed.cpp \
    $${QFIPATH}/qaltimeter.cpp \
    $${QFIPATH}/qamchronograph.cpp \
    $${QFIPATH}/qamflightinstrument.cpp \
    $${QFIPATH}/qamturncoordinator.cpp \
    $${QFIPATH}/qamtachymeter.cpp \
    $${QFIPATH}/QHA.cpp \
    $${UDPPATH}/dataref.cpp \
    $${UDPPATH}/qamudpsocket.cpp \
    $${UDPPATH}/xplaneudpworker.cpp

HEADERS  += test.h \
    $${QFIPATH}/qairspeed.h \
    $${QFIPATH}/qaltimeter.h \
    $${QFIPATH}/qamchronograph.h \
    $${QFIPATH}/qamflightinstrument.h \
    $${QFIPATH}/qamturncoordinator.h \
    $${QFIPATH}/qamtachymeter.h \
    $${QFIPATH}/QHA.h \
    $${UDPPATH}/dataref.h \
    $${UDPPATH}/qamudpsocket.h \
    $${UDPPATH}/xplaneudpworker.h

FORMS    += test.ui
