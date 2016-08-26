#-------------------------------------------------
#
# Project created by QtCreator 2015-11-04T16:48:06
#
#-------------------------------------------------

QT       += widgets network opengl sql script

TARGET = QSysSet
TEMPLATE = lib

#引入天池项目
DEFINES += TIANCHI_EXPORT
LIBS += -L$$PWD/../tianchi/lib/ -ltianchi

#定义编译选项，在.h文件中就可以使用：#if defined(QSYSSET_LIBRARY)
DEFINES += QSYSSET_LIBRARY

SOURCES += qsysset.cpp \
    qsyssetcontroller.cpp \
    qsyssethelper.cpp

HEADERS += qsysset.h\
        qsysset_global.h \
    qsyssetcontroller.h \
    qsyssethelper.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

#自己定义的参数，在include.pri中区分程序类型
CONFIG += dllfile

include($$PWD/../include.pri)

#如果不引入会找不到天池项目的头文件
include($$PWD/../tianchi/tianchi.pri)
