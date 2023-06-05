QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    accountsettings.cpp \
    chatlistitem.cpp \
    chatmessageitem.cpp \
    chatpage.cpp \
    chatsettings.cpp \
    createchat.cpp \
    createpost.cpp \
    createshoal.cpp \
    createsurvey.cpp \
    inbox.cpp \
    indexbutton.cpp \
    login.cpp \
    main.cpp \
    monitor.cpp \
    monitoraccountitem.cpp \
    monitorlistitem.cpp \
    palcard.cpp \
    palshowcase.cpp \
    postcard.cpp \
    postfeed.cpp \
    postsurvey.cpp \
    profilecard.cpp \
    profileeditor.cpp \
    profileeditorlink.cpp \
    profileeditorpal.cpp \
    profilepage.cpp \
    reeffeed.cpp \
    reeflist.cpp \
    shoalfeed.cpp \
    shoalhome.cpp \
    shoallist.cpp \
    tidepool.cpp \
    ../user/account.cpp \
    ../user/accountio.cpp \
    ../user/userconfig.cpp \
    ../database/database.cpp \
    ../database/userdb.cpp \
    ../database/chatdb.cpp \
    ../database/monitordb.cpp \
    ../database/contentdb.cpp \
    ../database/profiledb.cpp \
    ../profile/profile.cpp \
    ../profile/profileio.cpp \
    ../profile/pal.cpp \
    ../chat/chat.cpp \
    ../chat/message.cpp \
    ../chat/chatio.cpp \
    ../monitor/reporter.cpp \
    ../monitor/reportaggregator.cpp \
    ../monitor/monitoritem.cpp \
    ../content/post.cpp \
    ../content/postio.cpp \
    ../content/shoal.cpp \
    userfeed.cpp

HEADERS += \
    accountsettings.h \
    chatlistitem.h \
    chatmessageitem.h \
    chatpage.h \
    chatsettings.h \
    createchat.h \
    createpost.h \
    createshoal.h \
    createsurvey.h \
    inbox.h \
    indexbutton.h \
    login.h \
    monitor.h \
    monitoraccountitem.h \
    monitorlistitem.h \
    palcard.h \
    palshowcase.h \
    postcard.h \
    postfeed.h \
    postsurvey.h \
    profilecard.h \
    profileeditor.h \
    profileeditorlink.h \
    profileeditorpal.h \
    profilepage.h \
    reeffeed.h \
    reeflist.h \
    shoalfeed.h \
    shoalhome.h \
    shoallist.h \
    tidepool.h \
    ../user/account.h \
    ../user/accountio.h \
    ../user/userconfig.h \
    ../database/database.h \
    ../database/userdb.h \
    ../database/chatdb.h \
    ../database/monitordb.h \
    ../database/contentdb.h \
    ../database/profiledb.h \
    ../profile/profile.h \
    ../profile/profileio.h \
    ../profile/pal.h \
    ../chat/chat.h \
    ../chat/message.h \
    ../chat/chatio.h \
    ../monitor/reporter.h \
    ../monitor/reportaggregator.h \
    ../monitor/monitoritem.h \
    ../content/post.h \
    ../content/postio.h \
    ../content/shoal.h \
    tidepoolbase.h \
    userfeed.h

FORMS += \
    accountsettings.ui \
    chatlistitem.ui \
    chatmessageitem.ui \
    chatpage.ui \
    chatsettings.ui \
    createchat.ui \
    createpost.ui \
    createshoal.ui \
    createsurvey.ui \
    inbox.ui \
    indexbutton.ui \
    login.ui \
    monitor.ui \
    monitoraccountitem.ui \
    monitorlistitem.ui \
    palcard.ui \
    palshowcase.ui \
    postcard.ui \
    postfeed.ui \
    postsurvey.ui \
    profilecard.ui \
    profileeditor.ui \
    profileeditorlink.ui \
    profileeditorpal.ui \
    profilepage.ui \
    reeflist.ui \
    shoallist.ui \
    tidepool.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
