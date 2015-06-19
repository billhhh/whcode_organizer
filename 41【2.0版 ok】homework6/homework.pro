#-------------------------------------------------
#
# Project created by QtCreator 2015-01-21T09:00:24
#
#-------------------------------------------------

QT       += core gui

TARGET = homework
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    showdocument.cpp

HEADERS  += mainwindow.h \
    showdocument.h

FORMS    += mainwindow.ui \
    showdocument.ui

CONFIG +=axcontainer

LIBS +=-lqaxserver \
       -lqaxcontainer
