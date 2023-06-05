#include "postcard.h"
#include "ui_postcard.h"

PostCard::PostCard(content::Post* p, QWidget* parent) :
    QWidget(parent), ui(new Ui::PostCard), post(p) {
    ui->setupUi(this);

    ui->timestamp->setText(QString::fromStdString(post->get_date()));
    ui->body->setText(QString::fromStdString(post->get_message()));
    ui->poster->setText(
        QString::fromStdString(post->get_user()->get_username()));
    ui->shoal->setText(QString::fromStdString(post->get_shoal().get_tag()));

    QPalette palette = *Theme::get(post->get_shoal().get_theme());
    ui->shoal->setPalette(palette);
}

PostCard::~PostCard()
{
    delete ui;
    delete post;
}

void PostCard::on_reportButton_clicked() { emit report(post); }

void PostCard::on_shoal_clicked() { emit shoal(post->get_shoal()); }

void PostCard::on_poster_clicked() { emit profile(post->get_user()); }
