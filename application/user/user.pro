TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle

QT += sql core                # this should be added

SOURCES += \
        accountio.cpp \
        main.cpp \
        account.cpp \
        userconfig.cpp \
        ../database/database.cpp \
        ../database/userdb.cpp

HEADERS += \
   account.h \
   accountio.h \
   userconfig.h \
   ../database/database.h \
   ../database/userdb.h

# if you have pthread errors, comment/uncomment the next line
LIBS += -pthread
SOURCES += ../../gtest/googletest/src/gtest-all.cc
INCLUDEPATH += ../../gtest \
               ../../gtest/googletest \
               ../../gtest/googletest/include \
               ../../gtest/googletest/include/gtest
