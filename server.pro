#-------------------------------------------------
#
# Project created by QtCreator 2016-02-02T12:17:07
#
#-------------------------------------------------

QT       += core gui network script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += SERVER_CONSOLE

TARGET = CardServer
TEMPLATE = app

SOURCES += server/main.cpp\
    server/windowcontroller.cpp \
    server/serverwindows.cpp \
    server/clientsocket.cpp \
    server/broadcastsocket.cpp \
    server/gameengine.cpp

HEADERS  += server/windowcontroller.h \
    server/serverwindows.h \
    server/clientsocket.h \
    server/broadcastsocket.h \
    server/gameengine.h

include($$PWD/command/command.pri)
include($$PWD/network/network.pri)
include($$PWD/data/script.pri)
include($$PWD/option.pri)

CONFIG(SERVER_CONSOLE){
    DEFINES += SERVER_CONSOLE
    QT -= gui


    greaterThan(QT_MAJOR_VERSION, 4): QT -= widgets
    message("Console mode only")
}

!CONFIG(SERVER_CONSOLE){
    message("Server gui enabled")

    SOURCES  += server/optionwindows.cpp
    HEADERS  += server/optionwindows.h

    FORMS    += server/optionwindows.ui \
        server/serverwindows.ui
}
