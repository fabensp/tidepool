#include "login.h"
#include "ui_login.h"

Login::Login(user::Account* a, db::Database* db, QWidget* parent) :
    QWidget(parent), ui(new Ui::Login), a(a), aio((db::UserDB*)db),
    pio((db::ProfileDB*)db) {
    ui->setupUi(this);

    ui->login->hide();
    ui->signup->hide();
    ui->invalidLogin->hide();
    ui->enthusiastInfo->hide();
}

Login::~Login() { delete ui; }

void Login::on_loginSelect_clicked() {
    ui->loginSelect->setChecked(true);
    ui->signupSelect->setChecked(false);
    ui->login->show();
    ui->signup->hide();
    ui->invalidLogin->hide();
}

void Login::on_signupSelect_clicked() {
    ui->signupSelect->setChecked(true);
    ui->loginSelect->setChecked(false);
    ui->signup->show();
    ui->login->hide();
    ui->invalidLogin->hide();
}

void Login::on_submitL_clicked() {
    // verify login with database, if fails show error popup
    a->set_email(ui->emailFieldL->text().toStdString());
    if (aio.verify(*a, ui->passFieldL->text().toStdString())) {
        if (a->get_access() != 0) emit validated();
        else {
            ui->invalidLogin->show();
            ui->invalidLabel->setText("Account Banned");
        }
    } else {
        ui->invalidLogin->show();
        ui->invalidLabel->setText("Invalid Credentials");
    }
}

void Login::on_submitS_clicked() {
    QPalette p;
    int fail = 0;

    // error flag setup
    p.setColor(QPalette::Base, QColor::fromRgb(255, 200, 200));
    p.setColor(QPalette::Window, QColor::fromRgb(255, 200, 200));
    ui->invalidLabel->setText("");

    // if email too short
    if (ui->emailFieldS->text().length() < 6) {
        ui->emailFieldS->setPalette(p);
        fail = 1;
    }

    // username too short
    if (ui->userFieldS->text().length() < 3) {
        ui->userFieldS->setPalette(p);
        fail = 1;
    }

    // password too short
    if (ui->passFieldS->text().length() < 8) {
        ui->passFieldS->setPalette(p);
        fail = 1;
    }

    // show error popup for too short
    if (fail) {
        ui->invalidLogin->show();
        ui->invalidLabel->setText("Field(s) Too Short");
        return;
    }

    // error popup for mismatching passwords
    if (ui->passFieldS->text() != ui->confirmFieldS->text()) {
        ui->invalidLogin->show();
        ui->invalidLabel->setText("Passwords Must Match");
        ui->confirmFieldS->setPalette(p);
        return;
    }

    // populate loacl account object with info
    a->set_username(ui->userFieldS->text().toStdString());
    a->set_email(ui->emailFieldS->text().toStdString());

    // if enthusiast,
    if (ui->enthusiastButton->isChecked()) {
        // and underage,
        if (ui->underageButton->isChecked()) {
            // set associated access level and require guardian
            a->set_access(1 + 8);
            if (ui->guardianField->text().length() < 3) {
                ui->guardianField->setPalette(p);
                ui->invalidLogin->show();
                ui->invalidLabel->setText("Invalid Guardian Username");
                return;
            }
            a->set_guardianId(ui->guardianField->text().toInt());
        } else a->set_access(2 + 8); // if not underage, just set access level
    } else if (ui->organizationButton->isChecked()) { // if organization,
        a->set_access(4 + 8);                         // give access level
    } else { // otherwise, require selection of one of those two
        ui->invalidLogin->show();
        ui->invalidLabel->setText("Select Account Type");
        ui->typeLabel->setPalette(p);
        return;
    }

    // if no immediate issues, try to insert to database and flag if error
    int insert = aio.insert(*a, ui->passFieldS->text().toStdString());
    if (insert == 1) {
        pio.create_profile(a->get_id(),
                           ui->fishdayFieldS->text().toStdString());
        emit validated();
    } else if ((insert & 8) == 8) {
        ui->invalidLogin->show();
        ui->invalidLabel->setText("Invalid Guardian Username");
        ui->guardianField->setPalette(p);
    } else if ((insert & 4) == 4) {
        ui->invalidLogin->show();
        ui->invalidLabel->setText("Email Already In Use");
        ui->emailFieldS->setPalette(p);
    } else if ((insert & 2) == 2) {
        ui->invalidLogin->show();
        ui->invalidLabel->setText("Username Already In Use");
        ui->userFieldS->setPalette(p);
    }
}

void Login::on_enthusiastButton_clicked() {
    ui->enthusiastButton->setChecked(true);
    ui->organizationButton->setChecked(false);
    ui->enthusiastInfo->show();
}

void Login::on_organizationButton_clicked() {
    ui->organizationButton->setChecked(true);
    ui->enthusiastButton->setChecked(false);
    ui->enthusiastInfo->hide();
}

void Login::on_underageButton_toggled(bool checked) {
    if (checked) ui->guardianField->setEnabled(true);
    else ui->guardianField->setEnabled(false);
}
