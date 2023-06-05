#include "reeflist.h"
#include "ui_reeflist.h"

ReefList::ReefList(user::Account* user, db::Database* db, QWidget* parent) :
    QWidget(parent), ui(new Ui::ReefList), user(user), pio((db::ProfileDB*)db),
    db(db) {
    ui->setupUi(this);

    // get profile of user
    profile::Profile p;
    pio.pull_profile_id(p, user->get_id());

    // populate ui list
    reef = p.get_reef();
    for (int i = 0; i < (int)reef.size(); i++) {
        if (reef[i].get_access() == 0) continue;
        IndexButton* w = new IndexButton(i, QString::fromStdString(reef[i].get_username()));
        ui->listLayout->addWidget(w);
        connect(w, &IndexButton::on_click, this, &ReefList::get_click);
    }
}

ReefList::~ReefList()
{
    delete ui;
}

void ReefList::get_click(int i) { emit open_profile(&reef[i]); }
