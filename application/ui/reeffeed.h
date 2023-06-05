#ifndef REEFFEED_H
#define REEFFEED_H

#include "../content/postio.h"
#include "postfeed.h"

/**
 * @brief ReefFeed is a post feed for an aggregation of posts from user's reef
 */
class ReefFeed : public PostFeed {
public:
    ReefFeed(user::Account* user, db::Database* db);

private:
    void refresh() override;
};

#endif // REEFFEED_H
