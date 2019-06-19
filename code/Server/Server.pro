TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lboost_system -lpthread -ljsoncpp -lmysqlclient

SOURCES += \
        main.cpp \
    netizen.cpp \
    networktransmission.cpp \
    privatechatroom.cpp \
    conversion.cpp \
    message.cpp \
    dbbroker.cpp \
    server.cpp \
    accountmanager.cpp \
    privatechat.cpp

HEADERS += \
    netizen.h \
    networktransmission.h \
    privatechatroom.h \
    conversion.h \
    message.h \
    dbbroker.h \
    server.h \
    accountmanager.h \
    privatechat.h
