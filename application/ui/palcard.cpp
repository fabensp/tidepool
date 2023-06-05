#include "palcard.h"
#include "ui_palcard.h"

PalCard::PalCard(profile::Pal* pal, QWidget* parent) :
    QWidget(parent), ui(new Ui::PalCard), pal(pal) {
    ui->setupUi(this);

    ui->groupBox->setTitle(QString::fromStdString(pal->get_name()));

    QImage image("../../images/" + QString::number(pal->get_avatarId())
                 + ".png");

    ui->label->setPixmap(QPixmap::fromImage(image));
}

PalCard::~PalCard()
{
    delete ui;
}

void PalCard::on_pushButton_clicked() { emit open_pal(pal); }
