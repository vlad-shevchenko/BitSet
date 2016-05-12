#-------------------------------------------------
#
# Project created by QtCreator 2016-05-12T15:42:13
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_testbitset
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_testbitset.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BitSet/release/ -lBitSet
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BitSet/debug/ -lBitSet
else:unix: LIBS += -L$$OUT_PWD/../BitSet/ -lBitSet

INCLUDEPATH += $$PWD/../BitSet
DEPENDPATH += $$PWD/../BitSet
