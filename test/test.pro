#-------------------------------------------------
#
# Project created by QtCreator 2016-05-25T19:35:26
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_bitset
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_bitset.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BitSet/release/ -lBitSet
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BitSet/debug/ -lBitSet
else:unix: LIBS += -L$$OUT_PWD/../BitSet/ -lBitSet

INCLUDEPATH += $$PWD/../BitSet
DEPENDPATH += $$PWD/../BitSet

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../BitSet/release/libBitSet.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../BitSet/debug/libBitSet.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../BitSet/release/BitSet.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../BitSet/debug/BitSet.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../BitSet/libBitSet.a
