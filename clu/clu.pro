#-------------------------------------------------
#
# Project created by QtCreator 2016-05-15T16:58:51
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = clu
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BitSet/release/ -lBitSet
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BitSet/debug/ -lBitSet
else:unix: LIBS += -L$$OUT_PWD/../BitSet/ -lBitSet

INCLUDEPATH += $$PWD/../BitSet
DEPENDPATH += $$PWD/../BitSet
