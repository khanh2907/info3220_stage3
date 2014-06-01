# -------------------------------------------------
# Project created by QtCreator 2010-04-28T20:25:30
# -------------------------------------------------
QT += testlib
QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = Test
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    testconfigreader.cpp
HEADERS += AutoTest.h \
    testconfigreader.h

OTHER_FILES += \
    config.txt


INCLUDEPATH += ../

config.path = $$OUT_PWD
config.files = config.txt

INSTALLS += config
