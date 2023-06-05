#include "createchat.h"
#include "ui_createchat.h"

CreateChat::CreateChat(user::Account* user, db::Database* db, QWidget* parent) :
    QWidget(parent), ui(new Ui::CreateChat),
    cio(new chat::ChatIO((db::ChatDB*)db)), user(user) {
    ui->setupUi(this);
}

CreateChat::~CreateChat()
{
    delete ui;
    delete cio;
}

void CreateChat::on_pushButton_clicked() {
    // construct new chat object
    chat::Chat c;
    c.set_title(ui->chatTitleLineEdit->text().toStdString());
    c.set_theme(ui->chatThemeComboBox->currentIndex());

    // send to database
    cio->create_chat(c);
    cio->add_member(c, user);
    ui->pushButton->setEnabled(false);
    emit exit();
}
