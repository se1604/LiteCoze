TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lboost_system -lpthread -ljsoncpp

SOURCES += \
        main.cpp \
    privatechat.cpp \
    netizen.cpp \
    networktransmission.cpp \
    privatechatroom.cpp \
    conversion.cpp \
    message.cpp \
    manager.cpp \
    dbmanger.cpp

HEADERS += \
    privatechat.h \
    netizen.h \
    networktransmission.h \
    privatechatroom.h \
    conversion.h \
    message.h \
    manager.h \
    dbmanger.h
