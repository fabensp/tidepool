#include "accountsettings.h"
#include "ui_accountsettings.h"

AccountSettings::AccountSettings(user::Account* a, user::AccountIO aio,
                                 user::Account* admin, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::AccountSettings), a(a), aio(aio) {

    ui->setupUi(this);

    // don't show access editing options if not admin
    if (admin == nullptr || admin->get_access() < 64
        || !admin->get_verified()) {
        ui->accessLabel->close();
        ui->accessWidget->hide();
    }

    // if underage, show guardian options
    if ((a->get_access() & 1) == 1 && admin != nullptr
        && admin->get_access() >= 64 && admin->get_verified()) {
        user::Account guardian;
        aio.pull(guardian, a->get_guardianId());
        ui->guardianField->setText(
                    QString::fromStdString(guardian.get_username()));
    } else {
        ui->guardianField->close();
        ui->guardianLabel->close();
    }

    // show current access level in ui
    int i = (a->get_access());
    if (!i) ui->selectAccess->setCurrentIndex(0);
    else if ((i & 1) == 1) ui->selectAccess->setCurrentIndex(1);
    else if ((i & 2) == 2) ui->selectAccess->setCurrentIndex(2);
    else if ((i & 4) == 4) ui->selectAccess->setCurrentIndex(3);
    else if ((i & 32) == 32) ui->selectAccess->setCurrentIndex(4);

    // show checkboxes
    if ((i & 8) == 0 && i) ui->approved->setChecked(true);
    if ((i & 16) == 16) ui->expert->setChecked(true);

    // hide error popup
    ui->invalidUpdate->hide();

    // populate current info
    ui->id->setText(QString::number(a->get_id()));
    ui->usernameField->setText(QString::fromStdString(a->get_username()));
    ui->emailField->setText(QString::fromStdString(a->get_email()));
}

AccountSettings::AccountSettings(user::Account* a, db::Database* db,
                                 QWidget* parent) :
    QWidget(parent),
    ui(new Ui::AccountSettings), a(a), aio((db::UserDB*)db) {

    ui->setupUi(this);

    // when editing own account, don't show anything for admins/mods
    ui->guardianField->close();
    ui->guardianLabel->close();
    ui->accessLabel->close();
    ui->accessWidget->hide();
    ui->invalidUpdate->hide();
    ui->id->setText(QString::number(a->get_id()));
    ui->usernameField->setText(QString::fromStdString(a->get_username()));
    ui->emailField->setText(QString::fromStdString(a->get_email()));
}

AccountSettings::~AccountSettings() { delete ui; }

void AccountSettings::on_saveButton_clicked() {
    QPalette p;
    int fail = 0;

    // error palette
    p.setColor(QPalette::Base, QColor::fromRgb(255, 200, 200));
    p.setColor(QPalette::Window, QColor::fromRgb(255, 200, 200));

    // if email too short, highlight and error
    if (ui->emailField->text().length() > 0
        && ui->emailField->text().length() < 6) {
        ui->emailField->setPalette(p);
        fail = 1;
    }

    // if username too short
    if (ui->usernameField->text().length() > 0
        && ui->usernameField->text().length() < 3) {
        ui->usernameField->setPalette(p);
        fail = 1;
    }

    // if password too short
    if (ui->passwordField->text().length() > 0
        && ui->passwordField->text().length() < 8) {
        ui->passwordField->setPalette(p);
        fail = 1;
    }

    // show popup
    if (fail) {
        ui->invalidUpdate->show();
        ui->invalidLabel->setText("Field(s) Too Short");
        return;
    }

    // update local object
    a->set_username(ui->usernameField->text().toStdString());
    a->set_email(ui->emailField->text().toStdString());

    // construct access level from selections
    int i = -1;
    if (ui->accessWidget->isVisible()) {
        if (ui->selectAccess->currentIndex() == 0)      i = 0;
        else if (ui->selectAccess->currentIndex() == 1) i = 1;
        else if (ui->selectAccess->currentIndex() == 2) i = 2;
        else if (ui->selectAccess->currentIndex() == 3) i = 4;
        else if (ui->selectAccess->currentIndex() == 4) i = 32;
        else if (ui->selectAccess->currentIndex() == 5) i = 64;

        if (!ui->approved->isChecked() && i) i += 8;
        if (ui->expert->isChecked() && i) i += 16;

        a->set_access(i);
    }

    // populate guardian from field
    user::Account guardian;
    if (i > -1 && (i & 1) == 1
        && aio.pull_username(guardian, ui->guardianField->text().toStdString()))
        a->set_guardianId(guardian.get_id());

    // update database, if update errors show popup message
    int update = aio.update(*a, ui->passwordField->text().toStdString());
    if (update == 1) emit validated();
    else if ((update & 2) == 2) {
        ui->usernameField->setPalette(p);
        ui->invalidUpdate->show();
        ui->invalidLabel->setText("Username Taken");
    } else if ((update & 4) == 4) {
        ui->emailField->setPalette(p);
        ui->invalidUpdate->show();
        ui->invalidLabel->setText("Email Already In Use");
    } else {
        qDebug() << update;
        ui->invalidUpdate->show();
        ui->invalidLabel->setText("Bad Credentials");
    }
}

void AccountSettings::on_selectAccess_currentIndexChanged(int index) {
    // if access changes to 1, display guardian settings
    if (index == 1) {
        ui->guardianField->show();
        ui->guardianLabel->show();
    } else {
        ui->guardianField->hide();
        ui->guardianLabel->hide();
    }
}
