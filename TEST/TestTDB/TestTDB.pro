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

INCLUDEPATH += . $${QFIPATH}

SOURCES += main.cpp\
        test.cpp \
    $${QFIPATH}/qairspeed.cpp \
    $${QFIPATH}/qaltimeter.cpp \
    $${QFIPATH}/qamchronograph.cpp \
    $${QFIPATH}/qamflightinstrument.cpp \
    $${QFIPATH}/qamturncoordinator.cpp \
    $${QFIPATH}/qamtachymeter.cpp \
    ../QamFlightInstruments-0.4/QHA.cpp \
    dataref.cpp

HEADERS  += test.h \
    $${QFIPATH}/qairspeed.h \
    $${QFIPATH}/qaltimeter.h \
    $${QFIPATH}/qamchronograph.h \
    $${QFIPATH}/qamflightinstrument.h \
    $${QFIPATH}/qamturncoordinator.h \
    $${QFIPATH}/qamtachymeter.h \
    ../QamFlightInstruments-0.4/QHA.h \
    dataref.h

FORMS    += test.ui
