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


SOURCES += client/main.cpp \
    client/mainwindow.cpp \
    client/game.cpp \
    client/player.cpp \
    client/card.cpp \
    client/cardwidget.cpp \
    client/cardelement.cpp \
    client/cardoverlay.cpp \
    client/playerwidget.cpp \
    client/creep.cpp \
    client/cardlayout.cpp

HEADERS  += client/mainwindow.h \
    client/game.h \
    client/player.h \
    client/card.h \
    client/cardwidget.h \
    client/cardelement.h \
    client/cardoverlay.h \
    client/playerwidget.h \
    client/creep.h \
    client/cardlayout.h

FORMS    += client/mainwindow.ui \
    client/gamelayout.ui

DISTFILES +=

RESOURCES += \
    client/images.qrc

include($$PWD/command/command.pri)
include($$PWD/network/network.pri)
include($$PWD/option.pri)
