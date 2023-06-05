#ifndef MONITOR_REPORT_AGGREGATOR_H
#define MONITOR_REPORT_AGGREGATOR_H

#include "../chat/message.h"
#include "../content/post.h"
#include "../database/database.h"
#include "../database/monitordb.h"
#include "../profile/profile.h"
#include "../user/account.h"
#include "monitoritem.h"
#include <vector>

namespace monitor {

class ReportAggregator {
public:
    /**
     * @brief ReportAggregator
     * @param user current user of the application
     * @param db monitor database ptr
     */
    ReportAggregator(user::Account* user, db::Database* db);

    ReportAggregator(){};

    /**
     * @brief fetch_among_posts searches through all posts
     * @param f filter to use
     * @param s search string
     * @param r 0 or 1, whether to only search among reported posts
     * @return vector of posts fitting criteria
     * filter options: 0 = username 1 = email 2 = user id 3 = profile display
     * name 4 = phrase in post body content 5 = shoal tag 6 = date posted
     */
    std::vector<MonitorItem*> fetch_among_posts(int f, std::string s,
                                                int r = 1);

    /**
     * @brief fetch_among_messages searches through all messages
     * @param f filter to use
     * @param s search string
     * @param r 0 or 1, whether to only search among reported posts
     * @return vector of messages fitting criteria
     * filter options: 0 = username 1 = email 2 = user id 3 = profile display
     * name 4 = phrase in message body 5 = chat id 6 = chat title 7 = date sent
     */
    std::vector<MonitorItem*> fetch_among_messages(int f, std::string s,
                                                   int r = 1);

    /**
     * @brief fetch_among_profiles searches through all profiles
     * @param f filter to use
     * @param s search string
     * @param r 0 or 1, whether to only search among reported posts
     * @return vector of profiles fitting criteria
     * filter options: 0 = username 1 = email 2 = user id 3 = profile display
     * name 4 = phrase in profile bio
     */
    std::vector<MonitorItem*> fetch_among_profiles(int f, std::string s,
                                                   int r = 1);

    /**
     * @brief unreport_post removes all post reports for a post
     * @param p post to unreport
     * @param admin account of the user executing the unreport
     * @return 1 = success 0 = fail
     * admin account must be verified and have an access >= 32
     */
    int unreport_post(content::Post& p, user::Account& admin);

    /**
     * @brief unreport_message removes all message reports for a message
     * @param m message to unreport
     * @param admin account of the user executing the unreport
     * @return 1 = success 0 = fail
     * admin account must be verified and have an access >= 32
     */
    int unreport_message(chat::Message& m, user::Account& admin);

    /**
     * @brief unreport_profile removes all profile reports for a profile
     * @param p profile to unreport
     * @param admin account of the user executing the unreport
     * @return 1 = success 0 = fail
     * admin account must be verified and have an access >= 32
     */
    int unreport_profile(user::Account& a, user::Account& admin);

private:
    user::Account* user;
    db::MonitorDB* mdb;
};

} // namespace monitor

#endif // MONITOR_REPORT_AGGREGATOR_H
