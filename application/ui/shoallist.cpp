#include "shoallist.h"
#include "ui_shoallist.h"

ShoalList::ShoalList(user::Account* user, db::Database* db, QWidget* parent) :
    QWidget(parent), ui(new Ui::ShoalList), user(user), pio((db::ContentDB*)db),
    db(db) {
    ui->setupUi(this);

    shoals = pio.pull_user_shoals(user);

    for (int i = 0; i < (int)shoals.size(); i++) {
        IndexButton* w = new IndexButton(i, QString::fromStdString(shoals[i]->get_tag()));
        ui->listLayout->addWidget(w);
        connect(w, &IndexButton::on_click, this, &ShoalList::get_click);
    }
}

ShoalList::~ShoalList()
{
    delete ui;
}

void ShoalList::get_click(int i) { emit open_shoal(shoals[i]); }
