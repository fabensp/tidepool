TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        log.cpp \
        main.cpp

HEADERS += \
   log.h \
   macro.h

# if you have pthread errors, comment/uncomment the next line
LIBS += -pthread
SOURCES += ../../gtest/googletest/src/gtest-all.cc
INCLUDEPATH += ../../gtest \
               ../../gtest/googletest \
               ../../gtest/googletest/include \
               ../../gtest/googletest/include/gtest
