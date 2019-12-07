#-------------------------------------------------
#
# Project created by QtCreator 2016-01-20T21:37:18
#
#-------------------------------------------------

QT       += core gui

CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MetashellUILibrary
TEMPLATE = lib
CONFIG += staticlib
DESTDIR = $$PWD/../Library

SOURCES +=\
        metashellmainwindow.cpp \
    metashellinterpreter.cpp \
    consolewidget.cpp \
    pragmawidget.cpp \
    treewidget.cpp \
    mdbcommands.cpp \
    piechartwidget.cpp \
    piechartcaptions.cpp \
    configreader.cpp

HEADERS  += metashellmainwindow.h \
    metashellinterpreter.h \
    consolewidget.h \
    pragmawidget.h \
    treewidget.h \
    mdbcommands.h \
    piechartwidget.h \
    piechartcaptions.h \
    DataTypes/jsondata.hpp \
    configreader.h

FORMS    += metashellmainwindow.ui \
    pragmawidget.ui \
    treewidget.ui \
    mdbcommands.ui
