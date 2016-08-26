# ===========================================================================
# 2015.11.04 wzguo  created
#
# 包含项目的基础文件
# ===========================================================================

TC_OUTPUT = $${PWD}/bin

#Debug模式下生成的文件后面加d
#CONFIG(debug, debug|release) {
#    TARGET = $${TARGET}d
#}

CONFIG(dllfile, dllfile|mainbase) {
    TC_OUTPUT = $${TC_OUTPUT}/modules
    DESTDIR = $$TC_OUTPUT
} else {
    DESTDIR = $$TC_OUTPUT
}

CONFIG(debug, debug|release) {
    TC_TMP = $${TC_OUTPUT}/debug
} else {
    TC_TMP = $${TC_OUTPUT}/release
}

#编译生成的文件位置
MOC_DIR = $$TC_TMP
OBJECTS_DIR = $$TC_TMP
UI_DIR = $$TC_TMP
RCC_DIR = $$TC_TMP

win32:LIBS += -lversion
win32-msvc*:LIBS += -ladvapi32 -lole32

HEADERS  += \
    $$PWD/base/qconsts.h \
    $$PWD/common/qtmodulemanager.h \
    $$PWD/base/qplugins.h \
    $$PWD/base/qcallonce.h \
    $$PWD/base/qsingleton.h \
    $$PWD/common/qtmodulecontroller.h \
    $$PWD/common/qtpluginfactory.h \
    $$PWD/base/objectfactory.h \
   # $$PWD/base/tianchi/tcglobal.h \
    $$PWD/base/qsysglobal.h \
    $$PWD/common/qcusstomhelper.h \
    $$PWD/custom/baseaction.h \
    $$PWD/common/qtintf.h \
    $$PWD/custom/exception.h \
    $$PWD/custom/iconhelper.h \
    $$PWD/base/widgetfactory.h \
    $$PWD/custom/basemenubar.h \
    $$PWD/custom/basemenu.h \
   # $$PWD/base/log/tclog.h

SOURCES += \
    $$PWD/common/qtmodulemanager.cpp \
    $$PWD/common/qtmodulecontroller.cpp \
    $$PWD/common/qtpluginfactory.cpp \
    $$PWD/common/qcusstomhelper.cpp \
    $$PWD/custom/baseaction.cpp \
    $$PWD/common/qtintf.cpp \
    $$PWD/custom/exception.cpp \
    $$PWD/custom/iconhelper.cpp \
    $$PWD/custom/basemenubar.cpp \
    $$PWD/custom/basemenu.cpp \
   # $$PWD/base/log/tclog.cpp

RESOURCES += \
    $$PWD/custom/main.qrc



