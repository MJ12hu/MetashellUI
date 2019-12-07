#-------------------------------------------------
#
# Project created by QtCreator 2016-01-20T21:37:18
#
#-------------------------------------------------

QT       += core gui

CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MetashellUI
TEMPLATE = app


SOURCES += main.cpp

HEADERS  +=


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../MetashellUILibrary/Library/release/ -lMetashellUILibrary
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../MetashellUILibrary/Library/debug/ -lMetashellUILibrary
else:unix: LIBS += -L$$PWD/../../MetashellUILibrary/Library/ -lMetashellUILibrary

INCLUDEPATH += $$PWD/../../MetashellUILibrary/src
DEPENDPATH += $$PWD/../../MetashellUILibrary/src

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../MetashellUILibrary/Library/release/libMetashellUILibrary.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../MetashellUILibrary/Library/debug/libMetashellUILibrary.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../MetashellUILibrary/Library/release/MetashellUILibrary.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../MetashellUILibrary/Library/debug/MetashellUILibrary.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../MetashellUILibrary/Library/libMetashellUILibrary.a
