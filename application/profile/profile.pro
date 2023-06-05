TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle

QT += sql core                # this should be added

SOURCES += \
        main.cpp \
        pal.cpp \
        profile.cpp \
        profileio.cpp \
        ../user/account.cpp \
        ../user/accountio.cpp \
        ../database/database.cpp \
        ../database/profiledb.cpp \
        ../database/userdb.cpp

HEADERS += \
    pal.h \
    profile.h \
    profileio.h \
    ../user/account.h \
    ../user/accountio.h \
    ../database/database.h \
    ../database/profiledb.h \
    ../database/userdb.h

# if you have pthread errors, comment/uncomment the next line
LIBS += -pthread
SOURCES += ../../gtest/googletest/src/gtest-all.cc
INCLUDEPATH += ../../gtest \
               ../../gtest/googletest \
               ../../gtest/googletest/include \
               ../../gtest/googletest/include/gtest
