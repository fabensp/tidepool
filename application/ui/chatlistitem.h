#ifndef CHATLISTITEM_H
#define CHATLISTITEM_H

#include "../chat/chat.h"
#include "tidepoolbase.h"
#include <QWidget>

namespace Ui {
class ChatListItem;
}

class Chat;

class ChatListItem : public QWidget
{
    Q_OBJECT

public:
    explicit ChatListItem(chat::Chat* c,
                          QWidget *parent = nullptr);
    ~ChatListItem();

signals:
    /**
     * @brief enter_chat emits when the chat item is clicked to enter
     * @param c chat represented by the button
     */
    void enter_chat(chat::Chat* c);

    /**
     * @brief open_settings emits when the settings button is clicked to edit
     * @param c chat represented by the button
     */
    void open_settings(chat::Chat* c);

private slots:
    void on_chat_clicked();

    void on_settingsButton_clicked();

private:
    Ui::ChatListItem *ui;
    chat::Chat* chat;
};

#endif // CHATLISTITEM_H
