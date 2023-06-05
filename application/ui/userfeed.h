#ifndef USERFEED_H
#define USERFEED_H

#include "../content/postio.h"
#include "postfeed.h"

/**
 * @brief UserFeed post feed specialized for posts by a single user
 */
class UserFeed : public PostFeed
{
public:
    UserFeed(user::Account* user, db::Database* db);
    ~UserFeed();

private:
    void refresh() override;
};

#endif // USERFEED_H
