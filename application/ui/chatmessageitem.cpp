#include "chatmessageitem.h"
#include "ui_chatmessageitem.h"

ChatMessageItem::ChatMessageItem(int outgoing,
                                 chat::Message* m,
                                 QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatMessageItem),
    m(m)
{
    ui->setupUi(this);

    ui->content->setText(QString::fromStdString(m->get_content()));
    ui->sender->setText(QString::fromStdString(m->get_sender().get_username()));
    ui->date->setText(QString::fromStdString(m->get_timestamp()));

    // shift the layout to push the message to the right and hide report button
    // for messages sent by the current user
    if (outgoing) {
        ui->receivedIndicator->hide();
        ui->sentSpacer->changeSize(1000000000, 0, QSizePolicy::Preferred);
        ui->content->setAlignment(Qt::AlignRight);
        ui->sender->close();
        ui->line->close();
    }
}

ChatMessageItem::ChatMessageItem(int outgoing, chat::Message* m, QPalette p,
                                 QWidget* parent) :
    ChatMessageItem(outgoing, m, parent) {
    this->setPalette(p);
}

ChatMessageItem::~ChatMessageItem()
{
    delete ui;
    delete m;
}

void ChatMessageItem::on_reportButton_clicked() { emit report(m); }
