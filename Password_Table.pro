#-------------------------------------------------
#
# Project created by QtCreator 2015-09-02T06:39:40
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Password_Table
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    chashgenerator.cpp \
    worker.cpp

HEADERS  += mainwindow.h \
    chashgenerator.h \
    worker.h

FORMS    += mainwindow.ui
