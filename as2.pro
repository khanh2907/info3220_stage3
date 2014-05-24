#-------------------------------------------------
#
# Project created by QtCreator 2014-03-17T13:17:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = as2
TEMPLATE = app

SOURCES += main.cpp\
    coordinate.cpp \
    ball.cpp \
    configreader.cpp \
    tablescene.cpp \
    tableview.cpp \
    as1ball.cpp \
    brick.cpp \
    paddle.cpp \
    player.cpp

HEADERS  += \
    coordinate.h \
    ball.h \
    configreader.h \
    tableview.h \
    tablescene.h \
    as1ball.h \
    brick.h \
    paddle.h \
    player.h

OTHER_FILES += \
    config.txt

CONFIG += c++11

config.path = $$OUT_PWD
config.files = config.txt

INSTALLS += config
