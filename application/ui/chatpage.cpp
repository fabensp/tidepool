#include "chatpage.h"
#include "ui_chatpage.h"

ChatPage::ChatPage(user::Account* u, db::Database* db, chat::Chat* c,
                   QWidget* parent) :
    QWidget(parent),
    ui(new Ui::ChatPage), user(u), chat(c),
    cio(new chat::ChatIO((db::ChatDB*)db)),
    r(new monitor::Reporter(u, (db::MonitorDB*)db)) {
    ui->setupUi(this);

    // when a chat is opened, set it to having been read
    cio->set_read(*chat, user);

    on_refreshButton_clicked();
}

ChatPage::~ChatPage() {
    delete ui;
    delete cio;
    delete chat;
    delete r;
}

void ChatPage::on_refreshButton_clicked() {

    // change chat theme color
    QPalette palette = *Theme::get(chat->get_theme());
    palette.setColor(QPalette::ButtonText, QColor::fromRgb(0));

    // delete all the messages that were in the feed
    QLayoutItem* child;
    while ((child = ui->msgFeedLayout->takeAt(0)) != 0) {
        child->widget()->hide();
        delete child;
    }

    // get 20 most recent messages from database
    cio->pull_num_messages(*chat, 20);

    // show each message
    for (chat::Message* m : chat->get_messages()) {
        // hide banned users
        if (m->get_sender().get_access() == 0) continue;

        int outgoing = m->get_sender().get_id() == user->get_id();

        // connect message to the page so report button clicks can be heard
        ChatMessageItem* cmi = new ChatMessageItem(outgoing, m, palette);
        ui->msgFeedLayout->insertWidget(0, cmi);
        connect(cmi, &ChatMessageItem::report, this, &ChatPage::on_report);
    }

    // always start at the bottom of the chat
    QScrollBar* scrollbar = ui->msgScroll->verticalScrollBar();
    QObject::connect(scrollbar, &QScrollBar::rangeChanged, this,
                     &ChatPage::scroll_bottom);
}

void ChatPage::scroll_bottom(int min, int max) {
    Q_UNUSED(min);
    ui->msgScroll->verticalScrollBar()->setValue(max);
}

void ChatPage::on_send_clicked() {
    // send message to database
    cio->new_message(*chat, ui->inputLine->toPlainText().toStdString(), user);
    ui->inputLine->clear();     // clear input field
    on_refreshButton_clicked(); // refresh chat
    cio->set_unread(*chat);     // set unread for everyone
    cio->set_read(*chat, user); // set read for sender
}

void ChatPage::on_report(chat::Message* m) { r->report(m); }

void ChatPage::on_exit_clicked() { emit exit(); }
