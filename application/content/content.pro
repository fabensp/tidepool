TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle

QT += sql core                # this should be added

SOURCES += \
        main.cpp \
        post.cpp \
        postio.cpp \
        shoal.cpp \
        ../user/account.cpp \
        ../user/accountio.cpp \
        ../database/database.cpp \
        ../database/userdb.cpp \
        ../database/contentdb.cpp

HEADERS += \
   post.h \
   postio.h \
   shoal.h \
   ../user/account.h \
   ../user/accountio.h \
   ../database/database.h \
   ../database/userdb.h \
   ../database/contentdb.h
