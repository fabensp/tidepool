TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle

QT += sql core                # this should be added

SOURCES += \
   monitoritem.cpp \
   reportaggregator.cpp \
   main.cpp \
   reporter.cpp \
   ../user/account.cpp \
   ../user/accountio.cpp \
   ../chat/message.cpp \
   ../content/post.cpp \
   ../content/shoal.cpp \
   ../profile/profile.cpp \
   ../profile/pal.cpp \
   ../database/database.cpp \
   ../database/userdb.cpp \
   ../database/chatdb.cpp \
   ../database/monitordb.cpp

# if you have pthread errors, comment/uncomment the next line
LIBS += -pthread
SOURCES += ../../gtest/googletest/src/gtest-all.cc
INCLUDEPATH += ../../gtest \
               ../../gtest/googletest \
               ../../gtest/googletest/include \
               ../../gtest/googletest/include/gtest

HEADERS += \
   monitoritem.h \
   reportaggregator.h \
   reporter.h \
   ../user/account.h \
   ../user/accountio.h \
   ../chat/message.h \
   ../content/post.h \
   ../content/shoal.h \
   ../profile/profile.h \
   ../profile/pal.h \
   ../database/database.h \
   ../database/userdb.h \
   ../database/chatdb.h \
   ../database/monitordb.h
