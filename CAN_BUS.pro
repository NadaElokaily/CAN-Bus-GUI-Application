#-------------------------------------------------
#
# Project created by QtCreator 2020-04-10T14:19:40
#
#-------------------------------------------------

QT       += core gui
QT       += xml
QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CAN_BUS
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    paintarea.cpp \
    propertieswindow.cpp

HEADERS  += mainwindow.h \
    paintarea.h \
    propertieswindow.h

FORMS    += mainwindow.ui \
    propertieswindow.ui

OTHER_FILES +=

RESOURCES += \
    AddEcuIcon.qrc \
    RemoveEcuIcon.qrc \
    saveIcon.qrc \
    loadIcon.qrc
