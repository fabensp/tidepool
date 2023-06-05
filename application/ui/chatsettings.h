#ifndef CHATSETTINGS_H
#define CHATSETTINGS_H

#include "../chat/chatio.h"
#include "indexbutton.h"
#include <QWidget>

namespace Ui {
class ChatSettings;
}

class ChatSettings : public QWidget
{
    Q_OBJECT

signals:
    /**
     * @brief open_profile emits when the profile of a chat member is opened
     * @param u account to open
     */
    void open_profile(user::Account *u);

    /**
     * @brief close emits when the user closes the chat settings screen
     */
    void close();

public:
    explicit ChatSettings(user::Account *user, db::Database *db, chat::Chat *c,
                          QWidget *parent = nullptr);
    ~ChatSettings();

private slots:
    void member_clicked(int i);

    void on_leaveButton_clicked();

    void on_confirmButton_clicked();

    void on_cancelLeaveButton_clicked();

    void on_confirmLeaveButton_clicked();

private:
    Ui::ChatSettings *ui;
    user::Account *user;
    chat::Chat *chat;
    chat::ChatIO *cio;
    vector<user::Account *> members;

    void refresh_members();
};

#endif // CHATSETTINGS_H
