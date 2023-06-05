#include "palshowcase.h"
#include "ui_palshowcase.h"

PalShowcase::PalShowcase(profile::Pal* pal, QWidget* parent) :
    QWidget(parent), ui(new Ui::PalShowcase), pal(pal) {
    ui->setupUi(this);

    ui->name->setText(QString::fromStdString(pal->get_name()));
    ui->species->setText(QString::fromStdString(pal->get_species()));
    ui->bday->setText(QString::fromStdString(pal->get_birthday()));
    ui->bio->setText(QString::fromStdString(pal->get_bio()));

    QImage image("../../images/" + QString::number(pal->get_avatarId())
                 + ".png");

    ui->photo->setPixmap(QPixmap::fromImage(image));
}

PalShowcase::~PalShowcase()
{
    delete ui;
}
