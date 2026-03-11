QT += testlib widgets
CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
TEMPLATE = app

SOURCES += tst_mainwindow.cpp \
    ../mainwindow.cpp \
    ../backend/BackendRunner.cpp

HEADERS += \
    ../mainwindow.h \
    ../backend/BackendRunner.h

FORMS += ../mainwindow.ui