#ifndef CHATMESSAGEITEM_H
#define CHATMESSAGEITEM_H

#include "../chat/message.h"
#include <QWidget>

namespace Ui {
class ChatMessageItem;
}

class ChatMessageItem : public QWidget
{
    Q_OBJECT

signals:
    /**
     * @brief report emits when the report button next to the chat is clicked
     * @param m message represented by the item
     */
    void report(chat::Message* m);

public:
    explicit ChatMessageItem(int outgoing, chat::Message* m,
                             QWidget* parent = nullptr);
    ChatMessageItem(int outgoing, chat::Message* m, QPalette p,
                    QWidget* parent = nullptr);
    ~ChatMessageItem();

private slots:
    void on_reportButton_clicked();

private:
    Ui::ChatMessageItem *ui;
    chat::Message* m;
};

#endif // CHATMESSAGEITEM_H
