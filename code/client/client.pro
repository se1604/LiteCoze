TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lboost_system -lpthread -ljsoncpp
SOURCES += \
        main.cpp \
    client.cpp \
    netizen.cpp \
    message.cpp \
    privatechatroom.cpp \
    conversion.cpp

HEADERS += \
    client.h \
    netizen.h \
    message.h \
    privatechatroom.h \
    conversion.h
