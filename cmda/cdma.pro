#-------------------------------------------------
#
# Project created by QtCreator 2016-02-17T20:54:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#在windows下使用第三方�?
LIBS += -LC:\mysql\lib -llibmysql
TARGET = cdma
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logindlg.cpp \
    mymysql.cpp \
    scriptdlg.cpp

HEADERS  += mainwindow.h \
    logindlg.h \
    mymysql.h \
    scriptdlg.h
