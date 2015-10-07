#-------------------------------------------------
#
# Project created by QtCreator 2015-05-13T11:24:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Radar
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    invertedmatrixwindow.cpp \
    invert.cpp

HEADERS  += mainwindow.h \
    invertedmatrixwindow.h \
    invert.h \
    Log.h

FORMS    += mainwindow.ui \
    invertedmatrixwindow.ui

QMAKE_CXXFLAGS += -std=c++0x
