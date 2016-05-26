#-------------------------------------------------
#
# Project created by QtCreator 2016-05-12T15:40:12
#
#-------------------------------------------------

QT       -= gui

TARGET = BitSet
TEMPLATE = lib

CONFIG += staticlib c++11

DEFINES += BITSET_LIBRARY

SOURCES += bitset.cpp \
    lexer.cpp \
    parser.cpp \
    expression_evaluator.cpp

HEADERS += bitset.h\
    bitset_global.h \
    symbols.h \
    lexer.h \
    parser.h \
    expression_evaluator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
