#-------------------------------------------------
#
# Project created by QtCreator 2013-06-01T15:01:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = joblc
TEMPLATE = app

RESOURCES     = application.qrc

SOURCES += mainwindow.cpp \
           utils.c \
           main.cpp

HEADERS  += mainwindow.h \
            utils.h

FORMS    += mainwindow.ui
