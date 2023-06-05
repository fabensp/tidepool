#include "indexbutton.h"
#include "ui_indexbutton.h"

IndexButton::IndexButton(int i, QString s, int f, QWidget *parent) :
    QWidget(parent), ui(new Ui::IndexButton), i(i) {
    ui->setupUi(this);
    if (f) ui->button->setFlat(true);
    ui->button->setText(s);
}

IndexButton::~IndexButton()
{
    delete ui;
}

void IndexButton::on_button_clicked()
{
    emit on_click(i);
}

