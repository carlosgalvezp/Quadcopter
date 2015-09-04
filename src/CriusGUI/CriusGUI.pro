#-------------------------------------------------
#
# Project created by QtCreator 2015-08-24T22:16:27
#
#-------------------------------------------------

QT       += core gui serialport opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

TARGET = CriusGUI
TEMPLATE = app
SOURCES += main.cpp\
        criusgui.cpp \
        serialcomm.cpp \
    qcustomplot.cpp \
    timeplot.cpp \
    utils.cpp \
    myglwidget.cpp

HEADERS  += criusgui.h \
            serialcomm.h \
    qcustomplot.h \
    timeplot.h \
    telemetry.h \
    utils.h \
    myglwidget.h

FORMS    += criusgui.ui