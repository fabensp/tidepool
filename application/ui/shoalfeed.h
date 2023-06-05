#ifndef SHOALFEED_H
#define SHOALFEED_H

#include "../content/postio.h"
#include "postfeed.h"

/**
 * @brief ShoalFeed is a post feed for an aggregation of the user's shoals posts
 */
class ShoalFeed : public PostFeed
{
public:
    ShoalFeed(user::Account* user, db::Database* db);

private:
    void refresh() override;
};

#endif // SHOALFEED_H
