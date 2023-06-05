#include "createsurvey.h"
#include "ui_createsurvey.h"

CreateSurvey::CreateSurvey(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateSurvey)
{
    ui->setupUi(this);
    ui->removeOptionButton->setEnabled(false);
}

CreateSurvey::~CreateSurvey()
{
    delete ui;
}

void CreateSurvey::on_addOptionButton_clicked()
{
    if (ui->options->itemAt(2))
        ui->addOptionButton->setEnabled(false);

    ui->options->addWidget(new QLineEdit());
    ui->removeOptionButton->setEnabled(true);
}


void CreateSurvey::on_removeOptionButton_clicked()
{
    if (!ui->options->itemAt(3)) {
        ui->removeOptionButton->setEnabled(false);
        ui->options->takeAt(2);
    } else
        ui->options->takeAt(3);

    ui->addOptionButton->setEnabled(true);
}

