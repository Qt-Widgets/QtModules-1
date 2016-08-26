#-------------------------------------------------
#
# Project created by QtCreator 2015-11-04T16:49:44
#
#-------------------------------------------------

QT       += widgets network opengl sql script
qtHaveModule(printsupport): QT += printsupport

TARGET = QGraphs

#dll文件
TEMPLATE = lib

#加载天池库，记录日志及其他功�?
DEFINES += TIANCHI_EXPORT
LIBS += -L$$PWD/../tianchi/lib/ -ltianchi

#定义编译选项，在.h文件中就可以使用�?#if defined(QGRAPHS_LIBRARY)
DEFINES += QGRAPHS_LIBRARY

SOURCES += qgraphs.cpp \
    qgraphscontroller.cpp \
    qgraphshelper.cpp \
    qcustomplot.cpp \
    frmcumentobject.cpp \
    qcpdocumentobject.cpp

HEADERS += qgraphs.h\
        qgraphs_global.h \
    qgraphscontroller.h \
    qgraphshelper.h \
    qcustomplot.h \
    frmcumentobject.h \
    qcpdocumentobject.h

#配置项，在include.pri文件中能用上
CONFIG += dllfile

unix {
    target.path = /usr/lib
    INSTALLS += target
}

#引入基础文件
include($$PWD/../include.pri)

#如果不引入会找不到天池项目的头文�?
include($$PWD/../tianchi/tianchi.pri)

FORMS += \
    frmcumentobject.ui
