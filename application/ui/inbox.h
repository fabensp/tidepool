#ifndef INBOX_H
#define INBOX_H

#include "../chat/chatio.h"
#include "../database/chatdb.h"
#include "chatlistitem.h"
#include "chatpage.h"
#include "chatsettings.h"
#include "createchat.h"
#include <QWidget>

namespace Ui {
class Inbox;
}

class Inbox : public QWidget
{
    Q_OBJECT

public:
    explicit Inbox(user::Account* user,
                   db::Database* db,
                   QWidget *parent = nullptr);
    ~Inbox();

signals:
    /**
     * @brief open_chat emits when user clicks a chat button to open
     * @param ch chat to open
     */
    void open_chat(chat::Chat* ch);

    /**
     * @brief open_page emits when a generic page is opened besides a chat
     * @param w widget to open
     * @param s string to title the main view box
     */
    void open_page(QWidget* w, QString s);

    /**
     * @brief create_chat emits when user clicks create new chat button
     */
    void create_chat();

    /**
     * @brief edit_chat emits when user clicks edit chat button
     * @param ch chat to edit
     */
    void edit_chat(chat::Chat* ch);

private:
    Ui::Inbox *ui;
    chat::ChatIO* cio;
    user::Account* user;
    std::vector<chat::Chat*> chat_list;
    monitor::Reporter* r;

    /**
     * @brief refresh_chat_list re-fetches the list of chats for the user
     */
    void refresh_chat_list();

private slots:
    void receive_chat_enter(chat::Chat* ch);
    void receive_settings_open(chat::Chat* ch);
    void on_refreshButton_clicked();
    void on_newMessageButton_clicked();
};

#endif // INBOX_H
