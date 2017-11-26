#-------------------------------------------------
#
# Project created by QtCreator 2017-11-26T04:50:22
#
#-------------------------------------------------

QT       += core gui opengl
CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Snake3D
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    openglwidget.cpp \
    model.cpp \
    light.cpp \
    material.cpp \
    camera.cpp \
    snakebody.cpp \
    snakehead.cpp \
    bloco.cpp \
    maca.cpp

HEADERS += \
    mainwindow.h \
    openglwidget.h \
    model.h \
    light.h \
    material.h \
    camera.h \
    snakebody.h \
    snakehead.h \
    bloco.h \
    maca.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    resources.qrc
