#-------------------------------------------------
#
# Project created by QtCreator 2016-12-02T21:16:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageReorganiser
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imagelogicreorganizer.cpp \
    help.cpp

HEADERS  += mainwindow.h \
    imagelogicreorganizer.h \
    help.h

FORMS    += mainwindow.ui \
    help.ui

win32 {
        RC_ICONS = icon.ico
}

DISTFILES +=
