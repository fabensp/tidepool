#include "postfeed.h"
#include "ui_postfeed.h"

PostFeed::PostFeed(user::Account *user, db::Database *db, QWidget *parent) :
    QWidget(parent), ui(new Ui::PostFeed), pio((db::ContentDB *)db),
    r(user, (db::MonitorDB *)db), user(user) {
    ui->setupUi(this);
    on_refresh_clicked();
    if ((user->get_id() & 8) == 8) ui->createPostButton->hide();
}

PostFeed::~PostFeed() { delete ui; }

void PostFeed::on_createPostButton_clicked() {
    // if no post already being created
    if (!ui->postFeedLayout->itemAt(2)) {
        CreatePost *w = new CreatePost(user, &pio);
        ui->postFeedLayout->addWidget(w);
        connect(w, &CreatePost::post, this, &PostFeed::creator_post);
        connect(w, &CreatePost::close, this, &PostFeed::close_creator);
    }
}

void PostFeed::close_creator() {
    QLayoutItem *child;
    while ((child = ui->postFeedLayout->takeAt(2)) != 0) {
        child->widget()->hide();
        delete child;
    }
}

void PostFeed::creator_post(content::Post* p) {
    p->set_user(user);
    pio.insert_post(*p);
    close_creator();
    on_refresh_clicked();
}

void PostFeed::on_refresh_clicked() {
    QLayoutItem *child;
    while ((child = ui->contentLayout->takeAt(0)) != 0) {
        child->widget()->hide();
        delete child;
    }

    // clear current posts then refresh
    posts.clear();
    refresh();
    for (content::Post *p : posts) {
        if (p->get_user()->get_access() == 0) continue;
        PostCard *pc = new PostCard(p, this);
        ui->contentLayout->addWidget(pc);
        connect(pc, &PostCard::report, this, &PostFeed::on_report);
        connect(pc, &PostCard::shoal, this, &PostFeed::on_shoal);
        connect(pc, &PostCard::profile, this, &PostFeed::on_profile);
    }
}

void PostFeed::on_report(content::Post *p) { r.report(p); }
void PostFeed::on_shoal(content::Shoal s) {
    emit open_shoal(new content::Shoal(s));
}
void PostFeed::on_profile(user::Account *u) {
    emit open_profile(new user::Account(*u));
}

void PostFeed::on_loadMoreButton_clicked() {
    // refresh feed without erasing current contents
    refresh();
    for (int i = ui->contentLayout->count(); i < (int)posts.size(); i++) {
        PostCard *pc = new PostCard(posts[i]);
        ui->contentLayout->addWidget(pc);
        connect(pc, &PostCard::report, this, &PostFeed::on_report);
    }
}

void PostFeed::on_createShoalButton_clicked() { emit create_shoal(); }
