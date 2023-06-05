
#include "shoalhome.h"
#include "ui_postfeed.h"

ShoalHome::ShoalHome(content::Shoal s, user::Account* user, db::Database* db) :
    PostFeed(user, db), s(s), prio((db::ProfileDB*)db) {
    on_refresh_clicked();

    // add frame at top of page
    QFrame* f = new QFrame();
    ui->postFeedLayout->insertWidget(0, f);
    f->setFrameStyle(QFrame::Panel);
    f->setLineWidth(3);
    f->setFrameShadow(QFrame::Raised);
    f->setLayout(new QHBoxLayout());

    // put label in frame for shoal description
    QLabel* l = new QLabel(QString::fromStdString(s.get_description()));
    f->layout()->addWidget(l);
    l->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // add button for joining/leaving shoal
    QString str = "Join Shoal";
    prio.pull_profile_id(curr_user, user->get_id());
    for (std::string& tag : curr_user.get_shoal_membership()) {
        if (tag == s.get_tag()) {
            str = "Leave Shoal";
            break;
        }
    }
    b = new QPushButton(str);
    f->layout()->addWidget(b);
    connect(b, &QPushButton::clicked, this, &ShoalHome::add_shoal);

    // set theme to shoal theme
    QPalette palette = *Theme::get(s.get_theme());
    palette.setColor(QPalette::ButtonText, QColor::fromRgb(0));
    f->setPalette(palette);
    f->setAutoFillBackground(true);
}

void ShoalHome::add_shoal() {
    for (std::string& tag : curr_user.get_shoal_membership()) {
        if (tag == s.get_tag()) {
            prio.remove_shoal_membership(curr_user, s.get_tag());
            b->setText("Join Shoal");
            on_refresh_clicked();
            emit update_shoallist();
            return;
        }
    }
    prio.add_shoal_membership(curr_user, s.get_tag());
    b->setText("Leave Shoal");
    on_refresh_clicked();
    emit update_shoallist();
}

void ShoalHome::refresh() {
    // pull 20 posts starting from the current vector index
    std::vector<content::Post*> pvec =
        pio.pull_num_shoal_posts(s, 20, posts.size());
    for (content::Post* p : pvec) {
        posts.push_back(p);
    }
    // if the most recent pulled post isn't the most recent post, hard refresh
    if (posts.size() > 0
        && pio.pull_num_shoal_posts(s, 1, 0)[0]->get_id()
               != posts[0]->get_id()) {
        on_refresh_clicked();
    }
}
