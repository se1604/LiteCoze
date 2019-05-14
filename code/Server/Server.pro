TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    server.cpp \
    manager.cpp \
    netizen.cpp \
    privatechatroom.cpp \
    message.cpp \
    network.cpp \
    conversion.cpp
#INCLUDEPATH += ../../x2struct-master
LIBS += -lboost_system -lpthread -ljsoncpp

HEADERS += \
    server.h \
    manager.h \
    netizen.h \
    privatechatroom.h \
    message.h \
    network.h \
    conversion.h
