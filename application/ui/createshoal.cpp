#include "createshoal.h"
#include "ui_createshoal.h"

CreateShoal::CreateShoal(user::Account* user, db::Database* db,
                         QWidget* parent) :
    QWidget(parent),
    ui(new Ui::CreateShoal), user(user), pio((db::ContentDB*)db),
    prio((db::ProfileDB*)db) {
    ui->setupUi(this);
}

CreateShoal::~CreateShoal()
{
    delete ui;
}

void CreateShoal::on_pushButton_clicked() {
    // construct shoal object
    content::Shoal s;
    s.set_tag(ui->shoalTagLineEdit->text().toStdString());
    s.set_desc(ui->shoalDescriptionLineEdit->text().toStdString());
    s.set_theme(ui->shoalThemeComboBox->currentIndex());
    s.set_creator_id(user->get_id());

    // send to database
    pio.create_shoal(&s);

    // add creator to shoal
    profile::Profile p;
    prio.pull_profile_id(p, user->get_id());
    prio.add_shoal_membership(p, s.get_tag());
    ui->pushButton->setEnabled(false);
    emit exit();
}
