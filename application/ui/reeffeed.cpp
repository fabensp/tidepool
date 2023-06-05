#include "reeffeed.h"
#include "ui_postfeed.h"

ReefFeed::ReefFeed(user::Account* user, db::Database* db) : PostFeed(user, db) {
    on_refresh_clicked();
    ui->createShoalButton->hide();
}

void ReefFeed::refresh() {
    // pull 20 posts starting from the current vector index
    std::vector<content::Post*> pvec =
        pio.pull_num_reef_posts(user, 20, posts.size());
    for (content::Post* p : pvec) {
        posts.push_back(p);
    }
    // if the most recent pulled post isn't the most recent post, hard refresh
    if (posts.size() > 0 && pio.pull_num_reef_posts(user, 1, 0)[0]->get_id()
        != posts[0]->get_id()) {
        on_refresh_clicked();
    }
}
