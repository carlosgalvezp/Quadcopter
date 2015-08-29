#-------------------------------------------------
#
# Project created by QtCreator 2015-08-24T22:16:27
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CriusGUI
TEMPLATE = app
SOURCES += main.cpp\
        criusgui.cpp \
        serialcomm.cpp

HEADERS  += criusgui.h \
            serialcomm.h

FORMS    += criusgui.ui
