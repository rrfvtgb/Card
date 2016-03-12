#-------------------------------------------------
#
# Project created by QtCreator 2015-12-08T21:22:31
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG   += C++11

TARGET = Card
TEMPLATE = app

INCLUDEPATH += $$PWD/client
DEPENDPATH += $$PWD/client

SOURCES += client/builder/main.cpp \
    client/view/cardwidget.cpp \
    client/view/cardelement.cpp \
    client/view/cardoverlay.cpp \
    client/view/playerwidget.cpp \
    client/view/cardlayout.cpp \
    client/data/creep.cpp \
    client/data/player.cpp \
    client/data/card.cpp \
    client/ui/serverlist.cpp \
    client/mainwindow.cpp \
    client/ui/menu.cpp \
    client/ui/gamewidget.cpp \
    client/control/game.cpp \
    client/control/oldprotocol.cpp \
    client/control/abstractnetworkprotocol.cpp \
    client/control/fancyprotocol.cpp \
    client/ui/serverinfo.cpp

HEADERS  += client/mainwindow.h \
    client/view/cardwidget.h \
    client/view/cardelement.h \
    client/view/cardoverlay.h \
    client/view/playerwidget.h \
    client/view/cardlayout.h \
    client/data/creep.h \
    client/data/player.h \
    client/data/card.h \
    client/ui/serverlist.h \
    client/ui/menu.h \
    client/ui/gamewidget.h \
    client/control/game.h \
    client/control/oldprotocol.h \
    client/control/abstractnetworkprotocol.h \
    client/control/fancyprotocol.h \
    client/ui/serverinfo.h

FORMS    += \
    client/ui/gamewidget.ui \
    client/ui/menu.ui \
    client/ui/serverlist.ui \
    client/ui/serverinfo.ui

DISTFILES +=

RESOURCES += \
    client/images.qrc

include($$PWD/command/command.pri)
include($$PWD/network/network.pri)
include($$PWD/option.pri)
