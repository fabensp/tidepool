#include "userfeed.h"
#include "ui_postfeed.h"

UserFeed::UserFeed(user::Account* user, db::Database* db) : PostFeed(user, db) {
    on_refresh_clicked();
    ui->createPostButton->hide();
    //    ui->refresh->hide();
    //    ui->loadMoreButton->hide();
    ui->createShoalButton->hide();
}

UserFeed::~UserFeed() { delete user; }

void UserFeed::refresh() {
    // pull 20 posts starting from the current vector index
    std::vector<content::Post*> pvec =
        pio.pull_num_user_posts(user, 20, posts.size());
    for (content::Post* p : pvec) {
        posts.push_back(p);
    }
    // if the most recent pulled post isn't the most recent post, hard refresh
    content::Post* first = pio.pull_num_user_posts(user, 1, 0).at(0);
    if (posts.size() > 0 && first && first->get_id() != posts[0]->get_id()) {
        on_refresh_clicked();
    }
    delete first;
}
