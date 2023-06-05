#include "profilecard.h"
#include "ui_profilecard.h"

ProfileCard::ProfileCard(profile::Profile* p, QWidget* parent) :
    QWidget(parent), ui(new Ui::ProfileCard), profile(p) {

    ui->setupUi(this);

    fill_info();

    QPalette palette = *Theme::get(profile->get_theme());
    palette.setColor(QPalette::ButtonText, QColor::fromRgb(0));
    this->setPalette(palette);

    // set pfp
    QImage image("../../images/" + QString::number(profile->get_avatar_id())
                 + ".png");
    ui->pfp->setPixmap(QPixmap::fromImage(image));
}

ProfileCard::~ProfileCard() {
    delete profile;
    delete ui;
}

void ProfileCard::fill_info() {

    // if organization, hide enthusiast-specific profile items
    if ((profile->get_account()->get_access() & 4) == 4) ui->citizen->hide();

    // populate info
    ui->username->setText(
        QString::fromStdString("@" + profile->get_account()->get_username()));
    ui->bio->setText(QString::fromStdString(profile->get_bio()));
    ui->dispname->setText(QString::fromStdString(profile->get_display_name()));
    ui->palBox->setTitle(QString::fromStdString(profile->get_display_name())
                         + "'s Pals");

    // add each pal
    for (profile::Pal* pal : profile->get_pals()) {
        PalCard* pc = new PalCard(pal);
        ui->palAreaLayout->addWidget(pc);
    }

    // add each link
    std::vector<std::string> ll = profile->get_link_labels();
    std::vector<std::string> la = profile->get_link_addresses();
    for (int i = 0; i < (int)ll.size(); i++) {
        LinkItem* w = new LinkItem(QString::fromStdString(ll[i]),
                                   QString::fromStdString(la[i]));
        ui->linkList->addItem(w);
    }
}

void ProfileCard::on_linkList_itemClicked(QListWidgetItem* item) {
    ((LinkItem*)item)->open();
}
