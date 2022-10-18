#-------------------------------------------------
#
# Project created by QtCreator 2022-10-17T17:57:27
#
#-------------------------------------------------

QT       += core gui
CONFIG += console
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tmp
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
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
        qOsgWidget.cpp \
    qosgwidgetui.cpp

HEADERS += \
        mainwindow.h \
        qOsgWidget.h \
        osgHeaders.h \
    qosgwidgetui.h


INCLUDEPATH += \
    F:/prjs/ThirdParty/osgQT/include \
    F:/prjs/ThirdParty/relyLib/osg/include

LIBS += -LF:/prjs/ThirdParty/relyLib/osg/lib
LIBS += \
    C:/Users/nash5/Desktop/tmp/osgQOpenGL.lib \
    OSG.lib \
    OSGUtil.lib \
    OSGViewer.lib \
    OSGGA.lib \
    OSGDB.lib \
    OSGText.lib \
    OpenThreads.lib \
    osgManipulator.lib \
    opengl32.lib \

FORMS += \
        mainwindow.ui \
    qosgwidgetui.ui
