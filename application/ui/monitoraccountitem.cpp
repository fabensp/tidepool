#include "monitoraccountitem.h"
#include "ui_monitoraccountitem.h"

MonitorAccountItem::MonitorAccountItem(user::Account *a, QWidget *parent) :
    QWidget(parent), ui(new Ui::MonitorAccountItem), a(a) {
    ui->setupUi(this);
    ui->userId->setText(QString::number(a->get_id()));
    ui->username->setText(QString::fromStdString(a->get_username()));
    ui->email->setText(QString::fromStdString(a->get_email()));
    ui->access->setText(QString::number(a->get_access()));
}

MonitorAccountItem::~MonitorAccountItem() { delete ui; }

void MonitorAccountItem::on_modifyButton_clicked() { emit modifyAccount(a); }
