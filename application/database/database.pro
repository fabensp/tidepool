TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle

QT += sql core                # this should be added

SOURCES += \
        chatdb.cpp \
        contentdb.cpp \
        database.cpp \
        main.cpp \
        monitordb.cpp \
        profiledb.cpp \
        userdb.cpp

DISTFILES += \
    db_todo

HEADERS += \
    chatdb.h \
    contentdb.h \
    database.h \
    monitordb.h \
    profiledb.h \
    userdb.h
