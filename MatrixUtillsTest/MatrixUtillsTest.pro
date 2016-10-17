QT += core
QT -= gui

TARGET = MatrixUtillsTest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH ''= ../Matrix
LIBS += -L../Matrix/debug/ -lMatrix

SOURCES += main.cpp

