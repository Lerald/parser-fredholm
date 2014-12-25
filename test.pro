#-------------------------------------------------
#
# Project created by QtCreator 2014-12-25T04:49:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app

LEXSOURCES = gram.l

YACCSOURCES = gram.y

SOURCES += main.cpp\
           base.cpp \
           corefunc.cpp \
        mainwindow.cpp

HEADERS  += mainwindow.h \
    base.h \
    corefunc.h

FORMS    += mainwindow.ui
