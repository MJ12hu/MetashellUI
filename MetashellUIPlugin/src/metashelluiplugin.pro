DEFINES += METASHELLUI_LIBRARY

# CodeCheckerPlugin files

SOURCES += \
    metashelloutputwindow.cpp \
    metashelluioptionspage.cpp \
    metashelluiplugin.cpp \
    optionswidget.cpp

HEADERS += \
    metashelloutputwindow.h \
    metashelluioptionspage.h \
    metashelluiplugin.h \
    metashelluiplugin_global.h \
    metashelluipluginconstants.h \
    optionswidget.h

CONFIG += c++11

# Qt Creator linking

## set the QTC_SOURCE environment variable to override the setting here
QTCREATOR_SOURCES = $$(QTC_SOURCE)
#isEmpty(QTCREATOR_SOURCES):QTCREATOR_SOURCES=/home/mj12hu/qt/qt-creator
isEmpty(QTCREATOR_SOURCES):QTCREATOR_SOURCES=../../../qt-creator

## set the QTC_BUILD environment variable to override the setting here
IDE_BUILD_TREE = $$(QTC_BUILD)
#isEmpty(IDE_BUILD_TREE):IDE_BUILD_TREE=/home/mj12hu/qt/qt-creator/build
isEmpty(IDE_BUILD_TREE):IDE_BUILD_TREE=../../../qt-creator/build

## uncomment to build plugin into user config directory
## <localappdata>/plugins/<ideversion>
##    where <localappdata> is e.g.
##    "%LOCALAPPDATA%\QtProject\qtcreator" on Windows Vista and later
##    "$XDG_DATA_HOME/data/QtProject/qtcreator" or "~/.local/share/data/QtProject/qtcreator" on Linux
##    "~/Library/Application Support/QtProject/Qt Creator" on Mac
# USE_USER_DESTDIR = yes

###### If the plugin can be depended upon by other plugins, this code needs to be outsourced to
###### <dirname>_dependencies.pri, where <dirname> is the name of the directory containing the
###### plugin's sources.

QTC_PLUGIN_NAME = MetashellUIPlugin
QTC_LIB_DEPENDS += \
    # nothing here at this time

QTC_PLUGIN_DEPENDS += \
    coreplugin \
    debugger

QTC_PLUGIN_RECOMMENDS += \
    # optional plugin dependencies. nothing here at this time

###### End _dependencies.pri contents ######

include($$QTCREATOR_SOURCES/src/qtcreatorplugin.pri)


FORMS += \
    optionswidget.ui

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
