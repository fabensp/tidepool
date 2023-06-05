#include "profilepage.h"
#include "ui_profilepage.h"

ProfilePage::ProfilePage(user::Account* user, user::Account profile_owner,
                         db::Database* db, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::ProfilePage), user(user),
    prio(new profile::ProfileIO((db::ProfileDB*)db)), psio((db::ContentDB*)db),
    r(user, (db::MonitorDB*)db) {
    ui->setupUi(this);

    // pull profile
    profile = new profile::Profile();
    prio->pull_profile_id(*profile, profile_owner.get_id());

    // set palette
    QPalette palette = *Theme::get(profile->get_theme());
    palette.setColor(QPalette::ButtonText, QColor::fromRgb(0));
    this->setPalette(palette);

    fill_info();

    // add user post feed
    ui->profileScrollLayout->addWidget(
        new UserFeed(new user::Account(profile_owner), db));

    // format fish date
    std::string str = prio->fish_time(profile);
    str = (str == "")
              ? " has been a Fish Enthusiast since " + profile->get_fish_date()
              : str;
    ui->fishday->setText(
        QString::fromStdString(profile->get_display_name() + str));
    if (profile->get_fish_date() == "") ui->fishday->hide();

    // set pfp
    QImage image("../../images/" + QString::number(profile->get_avatar_id())
                 + ".png");
    ui->pfp->setPixmap(QPixmap::fromImage(image));

    ui->addToReefButton->setText(QString::fromStdString(
        "Add " + profile->get_display_name() + " to Reef"));

    // if current user already has this profile in their reef, hide button
    profile::Profile curr_user;
    prio->pull_profile_id(curr_user, user->get_id());
    for (user::Account a : curr_user.get_reef()) {
        if (a.get_id() == profile->get_id()) {
            ui->addToReefButton->setText(QString::fromStdString(
                "Remove " + profile->get_display_name() + " from Reef"));
            break;
        }
    }
}

// constructor for just showing a profile, mainly for monitor view
ProfilePage::ProfilePage(user::Account* user, profile::Profile* p,
                         QWidget* parent) :
    QWidget(parent),
    ui(new Ui::ProfilePage), user(user), profile(p), prio(nullptr),
    psio(nullptr), r(nullptr, nullptr) {

    ui->setupUi(this);

    fill_info();

    // hide buttons that can open new pages, etc
    ui->contextButton->hide();
    ui->addToReefButton->hide();
    ui->viewShoals->hide();
    ui->viewReef->hide();
}

ProfilePage::~ProfilePage() {
    delete ui->profileScrollLayout->takeAt(3); // delete user post feed
    delete profile;
    delete ui;
}

void ProfilePage::fill_info() {
    if ((profile->get_account()->get_access() & 4) == 4) ui->citizen->hide();
    ui->username->setText(
        QString::fromStdString("@" + profile->get_account()->get_username()));
    ui->bio->setText(QString::fromStdString(profile->get_bio()));
    ui->dispname->setText(QString::fromStdString(profile->get_display_name()));
    ui->palBox->setTitle(QString::fromStdString(profile->get_display_name())
                         + "'s Pals");
    ui->viewReef->setText(
        QString::fromStdString(profile->get_display_name() + "'s Reef"));
    ui->viewShoals->setText(
        QString::fromStdString(profile->get_display_name() + "'s Shoals"));

    // if this profile belongs to current user
    if (user->get_id() == profile->get_account()->get_id()) {
        ui->addToReefButton->hide();
        ui->contextButton->setText("Edit Profile");
    } else {
        ui->contextButton->setText("!");
        ui->contextButton->setToolTip("Report Profile");
    }

    // show pals
    for (profile::Pal* pal : profile->get_pals()) {
        PalCard* pc = new PalCard(pal);
        ui->palAreaLayout->addWidget(pc);
        connect(pc, &PalCard::open_pal, this, &ProfilePage::open_pal);
    }

    // show links
    std::vector<std::string> ll = profile->get_link_labels();
    std::vector<std::string> la = profile->get_link_addresses();
    for (int i = 0; i < (int)ll.size(); i++) {
        LinkItem* w = new LinkItem(QString::fromStdString(ll[i]),
                                   QString::fromStdString(la[i]));
        ui->linkList->addItem(w);
    }
}

void ProfilePage::on_contextButton_clicked() {
    // change functionality depending on user
    if (ui->contextButton->text() == "!") {
        r.report(profile);
    } else if (ui->contextButton->text() == "Edit Profile"
               && profile->get_id() == user->get_id()) {
        emit enter_editor();
    }
}

void ProfilePage::on_linkList_itemClicked(QListWidgetItem* item) {
    ((LinkItem*)item)->open();
}

void ProfilePage::on_addToReefButton_clicked() {
    profile::Profile curr_user;
    prio->pull_profile_id(curr_user, user->get_id());
    for (user::Account a : curr_user.get_reef()) {
        if (a.get_id() == profile->get_id()) {
            prio->remove_reef(*profile, *user, *profile->get_account());
            ui->addToReefButton->setText(QString::fromStdString(
                "Add " + profile->get_display_name() + " to Reef"));
            emit update_reef();
            return;
        }
    }
    prio->add_user_to_reef(*profile, *user, *profile->get_account());
    ui->addToReefButton->setText(QString::fromStdString(
        "Remove " + profile->get_display_name() + " from Reef"));
    emit update_reef();
}

void ProfilePage::on_viewReef_clicked() {
    emit reef_view(profile->get_account());
}

void ProfilePage::on_viewShoals_clicked() {
    emit shoal_view(profile->get_account());
}

void ProfilePage::open_pal(profile::Pal* p) {
    QLayoutItem* child;
    while ((child = ui->palViewLayout->takeAt(0)) != 0) {
        child->widget()->hide();
        delete child;
    }
    PalShowcase* w = new PalShowcase(p);
    ui->palViewLayout->addWidget(w);
}
