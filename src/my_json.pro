#-------------------------------------------------
#
# Project created by QtCreator 2021-06-15T09:24:33
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++17
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = my_json
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS


# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
        json_src/json_src_qt.cpp

HEADERS += \
        mainwindow.h \
        json_src/json_src.h \
        json_src/json_base.h \
        json_src/json1.h \
        json_src/json2.h \
        json_src/json3.h

FORMS += \
        mainwindow.ui
