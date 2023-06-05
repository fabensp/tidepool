#include "profileeditorpal.h"
#include "ui_profileeditorpal.h"

ProfileEditorPal::ProfileEditorPal(profile::Pal* pal, QWidget* parent) :
    QWidget(parent), ui(new Ui::ProfileEditorPal), pal(pal) {
    ui->setupUi(this);

    ui->name->setText(QString::fromStdString(pal->get_name()));
    ui->species->setText(QString::fromStdString(pal->get_species()));
    ui->bday->setText(QString::fromStdString(pal->get_birthday()));
}

ProfileEditorPal::~ProfileEditorPal()
{
    delete ui;
}

void ProfileEditorPal::on_toolButton_clicked() { emit remove_pal(this, pal); }
