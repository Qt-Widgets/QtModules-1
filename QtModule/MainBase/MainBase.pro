#-------------------------------------------------
#
# Project created by QtCreator 2015-11-04T16:42:35
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

qtHaveModule(printsupport): QT += printsupport

#输出文件的名字
TARGET = MainBase

#文件类型，app->exe，主程序
TEMPLATE = app

DEFINES += TIANCHI_IMPORT
LIBS += -L$$PWD/../tianchi/lib/ -ltianchi

SOURCES += main.cpp \
    mainwindow.cpp \
    qshell.cpp \
    qshellhelper.cpp

HEADERS  += \
    mainwindow.h \
    qshell.h \
    qshellhelper.h

FORMS    += \
    mainwindow.ui

# CONFIG配置参数中没有mainbase，这个是自己加的便于在include.pri中使用
CONFIG += mainbase

include($$PWD/../include.pri)
include($$PWD/../tianchi/tianchi.pri)
