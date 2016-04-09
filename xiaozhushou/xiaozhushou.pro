#-------------------------------------------------
#
# Project created by QtCreator 2015-10-23T17:00:22
#
#-------------------------------------------------

QT       += core gui webkitwidgets network widgets
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = xiaozhushou
TEMPLATE = app


SOURCES += main.cpp\
        logging.cpp \
    kebiao.cpp \
    mingdan.cpp \
    gongneng.cpp\
    kejian.cpp \
    xueshengxinxi.cpp \
    zuoyeguanli.cpp \
    struct.cpp \
    wkebiao.cpp

HEADERS  += logging.h \
    kebiao.h \
    structs.h \
    mingdan.h \
    gongneng.h \
    kejian.h \
    xueshengxinxi.h \
    zuoyeguanli.h \
    wkebiao.h

FORMS    += logging.ui \
    kebiao.ui \
    mingdan.ui \
    gongneng.ui \
    kejian.ui \
    xueshengxinxi.ui \
    zuoyeguanli.ui \
    wkebiao.ui


RC_FILE = icon.rc

RESOURCES += \
    xiaozhushou.qrc
