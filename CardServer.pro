#-------------------------------------------------
#
# Project created by QtCreator 2016-02-02T12:17:07
#
#-------------------------------------------------

QT       += core gui network script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CardServer
TEMPLATE = app

SOURCES += server/main.cpp\
    server/optionwindows.cpp \
    server/windowcontroller.cpp \
    server/serverwindows.cpp \
    server/clientsocket.cpp \
    server/broadcastsocket.cpp \
    server/gameengine.cpp

HEADERS  += server/optionwindows.h \
    server/windowcontroller.h \
    server/serverwindows.h \
    server/clientsocket.h \
    server/broadcastsocket.h \
    server/gameengine.h

FORMS    += server/optionwindows.ui \
    server/serverwindows.ui

include($$PWD/command/command.pri)
include($$PWD/network/network.pri)
include($$PWD/data/script.pri)
include($$PWD/option.pri)
