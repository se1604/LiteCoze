TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lboost_system -lpthread -ljsoncpp
SOURCES += \
        main.cpp \
    clientui.cpp \
    client.cpp \
    conversion.cpp \
    netizen.cpp \
    privatechatroom.cpp \
    message.cpp \
    loginUI.cpp

HEADERS += \
    clientui.h \
    client.h \
    conversion.h \
    netizen.h \
    privatechatroom.h \
    message.h \
    loginUI.h
