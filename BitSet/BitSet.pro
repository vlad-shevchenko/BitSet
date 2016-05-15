#-------------------------------------------------
#
# Project created by QtCreator 2016-05-12T15:40:12
#
#-------------------------------------------------

QT       -= gui

TARGET = BitSet
TEMPLATE = lib

CONFIG += staticlib

DEFINES += BITSET_LIBRARY

SOURCES += bitset.cpp

HEADERS += bitset.h\
        bitset_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
