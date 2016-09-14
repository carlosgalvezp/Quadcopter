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
SOURCES += main.cpp                 \
           criusgui.cpp             \
           qcustomplot.cpp          \
           timeplot.cpp             \
           utils.cpp                \
           myglwidget.cpp           \
           serialcommthread.cpp     \
           serialdecoder.cpp        \
           guidata.cpp

HEADERS  += criusgui.h                          \
            qcustomplot.h                       \
            timeplot.h                          \
            utils.h                             \
            myglwidget.h                        \
            ../ArduinoFC/Telemetry_Protocol.h   \
            serialcommthread.h                  \
            serialdecoder.h                     \
            guidata.h                           \
            types.h

FORMS    += criusgui.ui

INCLUDEPATH += $$PWD/../../FlightController/hal/arduino/include
