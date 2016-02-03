#-------------------------------------------------
#
# Project created by QtCreator 2016-02-02T12:17:07
#
#-------------------------------------------------

QT       += core gui network script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CardServer
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        optionwindows.cpp \
    windowcontroller.cpp \
    serverwindows.cpp \
    clientsocket.cpp \
    network/packet.cpp \
    network/packetmanager.cpp \
    network/packet01message.cpp \
    broadcastsocket.cpp \
    gameengine.cpp

HEADERS  += optionwindows.h \
    windowcontroller.h \
    serverwindows.h \
    clientsocket.h \
    network/packet.h \
    network/packetmanager.h \
    network/packet01message.h \
    broadcastsocket.h \
    gameengine.h

FORMS    += optionwindows.ui \
    serverwindows.ui

Release:DESTDIR = release
Release:OBJECTS_DIR = release/.obj
Release:MOC_DIR = release/.moc
Release:RCC_DIR = release/.rcc
Release:UI_DIR = release/.ui

Debug:DESTDIR = debug
Debug:OBJECTS_DIR = debug/.obj
Debug:MOC_DIR = debug/.moc
Debug:RCC_DIR = debug/.rcc
Debug:UI_DIR = debug/.ui
