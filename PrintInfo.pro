#-------------------------------------------------
#
# Project created by QtCreator 2016-06-14T07:15:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PrintInfo
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    qgetcpu.cpp \
    processinfo.cpp \
    cpuinfo.cpp \
    versioninfo.cpp \
    meminfo.cpp \
    processinfolist.cpp

HEADERS  += widget.h \
    qgetcpu.h \
    processinfo.h \
    cpuinfo.h \
    versioninfo.h \
    meminfo.h \
    processinfolist.h \
    main.h

FORMS    += widget.ui
