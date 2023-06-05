#include "chatsettings.h"
#include "ui_chatsettings.h"

ChatSettings::ChatSettings(user::Account* user, db::Database* db, chat::Chat* c,
                           QWidget* parent) :
    QWidget(parent),
    ui(new Ui::ChatSettings), user(user), chat(c),
    cio(new chat::ChatIO((db::ChatDB*)db)) {
    ui->setupUi(this);

    // populate current info
    ui->titleField->setText(QString::fromStdString(chat->get_title()));
    ui->themeSelect->setCurrentIndex(chat->get_theme());
    refresh_members();
    ui->warning->hide();
}

ChatSettings::~ChatSettings()
{
    delete ui;
    delete cio;
}

void ChatSettings::on_confirmButton_clicked() {
    // send edits to database
    cio->update_chat(*chat, ui->titleField->text().toStdString(),
                     ui->themeSelect->currentIndex());

    // add member and refresh
    if (cio->add_member(*chat, ui->addMemberField->text().toStdString())) {
        refresh_members();
        ui->addMemberField->clear();
    }
}

void ChatSettings::refresh_members() {
    // clear list
    QLayoutItem* child;
    while ((child = ui->memberLayout->takeAt(0)) != 0) {
        child->widget()->hide();
        delete child;
    }
    for (user::Account* a : members) delete a;

    // pull members from database
    members = cio->pull_chat_members(*chat);

    // populate ui
    for (int i = 0; i < (int)members.size(); i++) {
        IndexButton* w = new IndexButton(
            i, QString::fromStdString(members[i]->get_username()), 1);
        ui->memberLayout->addWidget(w);
        connect(w, &IndexButton::on_click, this, &ChatSettings::member_clicked);
    }
}

void ChatSettings::on_leaveButton_clicked() { ui->warning->show(); }

void ChatSettings::on_cancelLeaveButton_clicked() { ui->warning->hide(); }

void ChatSettings::on_confirmLeaveButton_clicked() {
    cio->remove_member(*chat, user);
    emit close();
}

void ChatSettings::member_clicked(int i) { emit open_profile(members[i]); }
