#-------------------------------------------------
#
# Project created by QtCreator 2015-03-06T11:18:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = rkc7-22
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
        widget.cpp \
    myplot.cpp \
    qcustomplot.cpp \
    resdialog.cpp \
    myinputwarningdialog.cpp \
    myinputerrordialog.cpp \
    mygauss.cpp

HEADERS  += widget.h \
    myplot.h \
    qcustomplot.h \
    resdialog.h \
    myinputwarningdialog.h \
    myinputerrordialog.h \
    mygauss.h

FORMS    += widget.ui \
    myplot.ui \
    resdialog.ui \
    myinputwarningdialog.ui \
    myinputerrordialog.ui \
    mygauss.ui

# RESOURCES +=
