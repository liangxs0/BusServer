#-------------------------------------------------
#
# Project created by QtCreator 2017-10-30T18:41:37
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bus
TEMPLATE = app


SOURCES += main.cpp\
        bus.cpp \
    add.cpp \
    money.cpp \
    find.cpp \
    protocol.cpp \
    network.cpp

HEADERS  += bus.h \
    add.h \
    money.h \
    find.h \
    protocol.h \
    network.h

FORMS    += bus.ui \
    add.ui \
    money.ui \
    find.ui

RESOURCES += \
    icons.qrc
