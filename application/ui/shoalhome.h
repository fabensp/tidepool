
#ifndef SHOALHOME_H
#define SHOALHOME_H

#include "../profile/profileio.h"
#include "postfeed.h"
#include <QLabel>
#include <QPushButton>

/**
 * @brief ShoalHome is a special post feed for a specific shoal
 */
class ShoalHome : public PostFeed {

public:
    ShoalHome(content::Shoal s, user::Account* user, db::Database* db);

private:
    void refresh() override;
    void add_shoal();
    content::Shoal s;
    profile::ProfileIO prio;
    profile::Profile curr_user;
    QPushButton* b;
};

#endif // SHOALHOME_H
