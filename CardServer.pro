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
    broadcastsocket.cpp \
    gameengine.cpp \
    network/packet.cpp \
    network/packetmanager.cpp \
    network/packet01message.cpp \
    network/packet02information.cpp \
    network/packet0fstart.cpp \
    network/packet20rename.cpp \
    network/packet10addcard.cpp \
    network/packet11cardinfo.cpp \
    network/packet18enablecard.cpp \
    network/packet19disablecard.cpp \
    network/packet21playerready.cpp \
    network/packet22playerunprepared.cpp \
    network/packet28playermana.cpp \
    network/packet29playerenergy.cpp \
    network/packet30creature.cpp \
    network/packet31removecreature.cpp \
    network/packet38creaturedamage.cpp \
    network/packet39hp.cpp

HEADERS  += optionwindows.h \
    windowcontroller.h \
    serverwindows.h \
    clientsocket.h \
    broadcastsocket.h \
    gameengine.h \
    network/packet.h \
    network/packetmanager.h \
    network/packet01message.h \
    network/packet02information.h \
    network/packet0fstart.h \
    network/packet20rename.h \
    network/packet10addcard.h \
    network/packet11cardinfo.h \
    network/packet18enablecard.h \
    network/packet19disablecard.h \
    network/packet21playerready.h \
    network/packet22playerunprepared.h \
    network/packet28playermana.h \
    network/packet29playerenergy.h \
    network/packet30creature.h \
    network/packet31removecreature.h \
    network/packet38creaturedamage.h \
    network/packet39hp.h

FORMS    += optionwindows.ui \
    serverwindows.ui

# Proper build folder
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

# Export data
copydata.commands = $(COPY_DIR) $$shell_path($$PWD/data) $$shell_path($$OUT_PWD/data)
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
