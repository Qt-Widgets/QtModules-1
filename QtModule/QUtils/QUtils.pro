#-------------------------------------------------
#
# Project created by QtCreator 2015-11-04T16:44:08
#
#-------------------------------------------------

QT       += widgets network opengl sql script

TARGET = QUtils
TEMPLATE = lib

#定义编译选项，在.h文件中就可以使用：#if defined(QUTILS_LIBRARY)
DEFINES += QUTILS_LIBRARY

#引入天池项目
DEFINES += TIANCHI_EXPORT
LIBS += -L$$PWD/../tianchi/lib/ -ltianchi

SOURCES += qutils.cpp \
    frmutils.cpp \
    qutilscontroller.cpp \
    utilshelper.cpp

HEADERS += qutils.h\
        qutils_global.h \
    frmutils.h \
    qutilscontroller.h \
    utilshelper.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    frmutils.ui

#自定义参数项目
CONFIG += dllfile
include($$PWD/../include.pri)
include($$PWD/../tianchi/tianchi.pri)
