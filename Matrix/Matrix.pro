#-------------------------------------------------
#
# Project created by QtCreator 2016-10-13T17:43:51
#
#-------------------------------------------------

QT       -= gui

TARGET = Matrix
TEMPLATE = lib

DEFINES += MATRIX_LIBRARY

SOURCES += matrix.cpp

HEADERS += matrix.h\
        matrix_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
