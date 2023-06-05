#include "inbox.h"
#include "ui_inbox.h"

Inbox::Inbox(user::Account* user, db::Database* db, QWidget* parent) :
    QWidget(parent), ui(new Ui::Inbox), cio(new chat::ChatIO((db::ChatDB*)db)),
    user(user) {
    ui->setupUi(this);

    on_refreshButton_clicked();
}

Inbox::~Inbox()
{
    delete ui;
    delete cio;
}

void Inbox::receive_chat_enter(chat::Chat* ch) { emit open_chat(ch); }

void Inbox::receive_settings_open(chat::Chat* ch) { emit edit_chat(ch); }

void Inbox::on_refreshButton_clicked()
{
    // erase chats in ui
    QLayoutItem* child;
    while ((child = ui->chatListLayout->takeAt(0)) != 0) {
        child->widget()->hide();
        delete child;
    }
    for (chat::Chat* c : chat_list) delete c;

    // pull chats from database
    chat_list = cio->pull_num_chats(user, 20);

    // populate ui list
    for (chat::Chat* c : chat_list) {
        ChatListItem* cli = new ChatListItem(c);
        ui->chatListLayout->addWidget(cli);
        connect(cli, &ChatListItem::enter_chat,
                this, &Inbox::receive_chat_enter);
        connect(cli, &ChatListItem::open_settings, this,
                &Inbox::receive_settings_open);
    }
}

void Inbox::on_newMessageButton_clicked() { emit create_chat(); }
