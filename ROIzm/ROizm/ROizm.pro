#-------------------------------------------------
#
# Project created by QtCreator 2015-08-26T11:21:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ROizm
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    funcmaker.cpp

HEADERS  += mainwindow.h \
    funcmaker.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++0x
