#-------------------------------------------------
#
# Project created by QtCreator 2015-05-27T10:42:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MNK
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    mnk.cpp \
    matrix.cpp

HEADERS  += mainwindow.h \
    mnk.h \
    matrix.h

FORMS    += mainwindow.ui
