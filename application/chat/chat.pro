TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle

QT += sql core                # this should be added

SOURCES += \
        chat.cpp \
        chatio.cpp \
        main.cpp \
        message.cpp \
        ../user/account.cpp \
        ../user/accountio.cpp \
        ../database/database.cpp \
        ../database/chatdb.cpp \
        ../database/userdb.cpp

HEADERS += \
    chat.h \
    chatio.h \
    message.h \
    ../user/account.h \
    ../user/accountio.h \
    ../database/database.h \
    ../database/chatdb.h \
    ../database/userdb.h

# if you have pthread errors, comment/uncomment the next line
LIBS += -pthread
SOURCES += ../../gtest/googletest/src/gtest-all.cc
INCLUDEPATH += ../../gtest \
               ../../gtest/googletest \
               ../../gtest/googletest/include \
               ../../gtest/googletest/include/gtest
