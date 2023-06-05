#include "chatlistitem.h"
#include "ui_chatlistitem.h"

ChatListItem::ChatListItem(chat::Chat* c, QWidget* parent) :
    QWidget(parent), ui(new Ui::ChatListItem), chat(c) {
    ui->setupUi(this);

    ui->chat->setText(QString::fromStdString(chat->get_title()));

    QPalette p;

    // unset unread marker for read messages
    if (!chat->get_unread()) {
        p.setColor(QPalette::WindowText, Theme::Current.button().color());
        ui->unread->setPalette(p);
        ui->unread->setLineWidth(9);
        ui->frame->setFrameStyle(0);
    } else {
        p.setColor(QPalette::WindowText,
                   Theme::get(chat->get_theme())->button().color());
        ui->unread->setPalette(p);
    }
}

ChatListItem::~ChatListItem() { delete ui; }

void ChatListItem::on_chat_clicked() { emit enter_chat(chat); }

void ChatListItem::on_settingsButton_clicked() { emit open_settings(chat); }
