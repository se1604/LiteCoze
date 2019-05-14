TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS +=-lboost_system -lthread

SOURCES += \
        main.cpp

HEADERS += \
    client.h
