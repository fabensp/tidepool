#ifndef REPORTER_H
#define REPORTER_H

#include "../chat/message.h"
#include "../content/post.h"
#include "../database/monitordb.h"
#include "../profile/profile.h"
#include "../user/account.h"

namespace monitor {

class Reporter
{
public:
    /**
     * @brief Reporter
     * @param user current user of the application
     * @param db monitor database ptr
     */
    Reporter(user::Account* user, db::MonitorDB* db);

    Reporter(){};

    /**
     * @brief report reports a post on the platform
     * @param p post to report
     */
    void report(content::Post* p);

    /**
     * @brief report reports a message on the platform
     * @param m message to report
     */
    void report(chat::Message* m);

    /**
     * @brief report reports a profile on the platform
     * @param p profile to report
     */
    void report(profile::Profile* p);

private:
    user::Account* user; // current application user (reporter)
    db::MonitorDB* db;
};

}

#endif // REPORTER_H
