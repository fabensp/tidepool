#ifndef CREATECHAT_H
#define CREATECHAT_H

#include "../chat/chatio.h"
#include <QWidget>

namespace Ui {
class CreateChat;
}

class CreateChat : public QWidget
{
    Q_OBJECT

signals:
    /**
     * @brief exit emits when the chat creation is confirmed
     */
    void exit();

public:
    explicit CreateChat(user::Account *user, db::Database *db,
                        QWidget *parent = nullptr);
    ~CreateChat();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CreateChat *ui;
    chat::ChatIO *cio;
    user::Account *user;
};

#endif // CREATECHAT_H
