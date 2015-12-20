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
    cardwidget.cpp

HEADERS  += mainwindow.h \
    game.h \
    player.h \
    card.h \
    cardwidget.h

FORMS    += mainwindow.ui \
    gamelayout.ui

DISTFILES +=
