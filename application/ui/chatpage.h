#ifndef CHATPAGE_H
#define CHATPAGE_H

#include "../chat/chat.h"
#include "../chat/chatio.h"
#include "../monitor/reporter.h"
#include "chatmessageitem.h"
#include "tidepoolbase.h"
#include <QScrollBar>
#include <QWidget>

namespace Ui {
class ChatPage;
}

class ChatPage : public QWidget
{
    Q_OBJECT

signals:
    /**
     * @brief exit emits when the chat is exited via the back button
     */
    void exit();

public:
    explicit ChatPage(user::Account* user, db::Database* db, chat::Chat* c,
                      QWidget* parent = nullptr);
    ~ChatPage();

private slots:
    void on_refreshButton_clicked();

    void on_send_clicked();

    void on_report(chat::Message* m);

    void on_exit_clicked();

    void scroll_bottom(int, int);

private:
    Ui::ChatPage *ui;
    user::Account* user;
    chat::Chat* chat;
    chat::ChatIO* cio;
    monitor::Reporter* r;
    int id;
};

#endif // CHATPAGE_H
