TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

QT += widgets

SOURCES += main.cpp \
    consoletest.cpp \
    ludecompose.cpp \
    addcalculationsthread.cpp

HEADERS += \
    consoletest.h \
    ludecompose.h \
    addcalculationsthread.h
