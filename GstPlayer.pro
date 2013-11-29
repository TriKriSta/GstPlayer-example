#-------------------------------------------------
#
# Project created by QtCreator 2013-10-03T02:52:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GstPlayer
TEMPLATE = app

SOURCES += main.cpp \
    playerform.cpp \
    audioengine.cpp

INCLUDEPATH += "/usr/include/glib-2.0/"
INCLUDEPATH += "/usr/include/gstreamer-1.0/"
INCLUDEPATH += "/usr/lib/glib-2.0/include"

QMAKE_LFLAGS = -L/usr/lib/gstreamer-1.0/ -lgstreamer-1.0

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += gobject-2.0

HEADERS += \
    playerform.h \
    audioengine.h

FORMS += \
    playerform.ui
