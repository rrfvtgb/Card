#-------------------------------------------------
#
# Project created by QtCreator 2015-12-08T21:22:31
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Card
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    game.cpp \
    player.cpp \
    card.cpp \
    cardwidget.cpp \
    cardelement.cpp \
    cardoverlay.cpp \
    playerwidget.cpp \
    creep.cpp

HEADERS  += mainwindow.h \
    game.h \
    player.h \
    card.h \
    cardwidget.h \
    cardelement.h \
    cardoverlay.h \
    playerwidget.h \
    creep.h

FORMS    += mainwindow.ui \
    gamelayout.ui

DISTFILES +=

RESOURCES += \
    images.qrc

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
