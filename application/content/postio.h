
#ifndef CONTENT_POSTIO_H
#define CONTENT_POSTIO_H

#include "../content/post.h"
#include "../database/contentdb.h"
#include "../user/account.h"
#include "../user/accountio.h"

namespace content {

class PostIO
{
public:

    /**
     * @brief PostIO constructor that links to the content database
     * @param db Profile database
     */
    PostIO(db::ContentDB* db);

    /**
     * @brief remove_post removes a post from the application
     * @param p     Post to remove
     * @param admin The admin that initiated the remove
     * @return 1 if successful, 0 if not
     */
    int remove_post(Post& p, user::Account& admin);

    /**
     * @brief pull_post pulls a post from the database
     * @param p  Post to push the info into
     * @param id identifier of the post to pull
     * @return 1 if successful, 0 if not
     */
    int pull_post(Post& p, int id);

    /**
     * @brief insert_post insert a post into the database
     * @param p Post to insert
     * @return 1 if successful, 0 if not
     */
    int insert_post(Post& p);

    /**
     * @brief pull_num_reef_posts pull a certain number of posts from a users reef
     * @param user   User to pull reef posts for
     * @param n      Number of posts to pull
     * @param offset Where to start pulling from
     * @return 1 if successful, 0 if not
     */
    std::vector<Post*> pull_num_reef_posts(user::Account* user, int n,
                                           int offset = 0);

    /**
     * @brief pull_num_shoal_posts pull a certain number of posts from a users shoal
     * @param user   User to pull shoal posts for
     * @param n      Number of posts to pull
     * @param offset Where to start pulling from
     * @return 1 if successful, 0 if not
     */
    std::vector<Post*> pull_num_user_shoal_posts(user::Account* user, int n,
                                                 int offset = 0);

    /**
     * @brief pull_num_shoal_posts pull a certain number of posts from a given shoal
     * @param s      Shoal to pull posts from
     * @param n      Number of posts to pull
     * @param offset Where to start pulling posts from
     * @return 1 if successful, 0 if not
     */
    std::vector<Post*> pull_num_shoal_posts(Shoal s, int n, int offset = 0);

    /**
     * @brief pull_num_user_posts pulls a certain number of posts from a given user
     * @param user   User to pull posts of
     * @param n      Number of posts to pull
     * @param offset Where to start pulling posts from
     * @return 1 if successful, 0 if not
     */
    std::vector<Post*> pull_num_user_posts(user::Account* user, int n,
                                           int offset = 0);

    /**
     * @brief pull_user_shoals Pull all the shoals that belong to a given user
     * @param user Users who shoals to pull from
     * @return 1 if successful, 0 if not
     */
    std::vector<Shoal*> pull_user_shoals(user::Account* user);

    /**
     * @brief pull_trade pull a trade from the database
     * @param t  Trade to push info into
     * @param id Identifier of the trade
     * @return 1 if successful, 0 if not
     */
    int pull_trade(Trade& t, int id);

    /**
     * @brief create_trade create a new trade given information
     * @param p            Post to load info into
     * @param pal_offer_id Identifier for the pal being offered
     * @param offer_alt    Text to go along with the offer
     * @param pal_seek_id  Identifier for the pal on the trade block
     * @param seek_alt     Text to go along with the pal on the trade block
     * @return 1 if successful, 0 if not
     */
    int create_trade(Post&p, int pal_offer_id, string offer_alt, int pal_seek_id, string seek_alt);

    /**
     * @brief pull_survey pull a survey from the database
     * @param s  Survey to push info into
     * @param id Identifier of the survey
     * @return 1 if successful, 0 if not
     */
    int pull_survey(Survey& s, int id);

    /**
     * @brief create_survey Create a survey with the given information
     * @param p       Post to load the survey into
     * @param opt1msg Label for option 1
     * @param opt2msg Label for option 2
     * @param opt3msg Label for option 3
     * @param opt4msg Label for option 4
     * @return 1 if successful, 0 if not
     */
    int create_survey(Post&p, string opt1msg, string opt2msg, string opt3msg, string opt4msg);

    /**
     * @brief pull_event pull an event from the database
     * @param e  Event to push info into
     * @param id Identifier of the event
     * @return 1 if successful, 0 if not
     */
    int pull_event(Event& e, int id);

    /**
     * @brief create_event create an event with the given information
     * @param p          Post to event load info into
     * @param title      Title of the event
     * @param start      Start time of the event
     * @param end        End time of the event
     * @param link_label Label of the link of the event website
     * @param link       Link to the event website
     * @return 1 if successful, 0 if not
     */
    int create_event(Post&p, string title, string start, string end, string link_label, string link);

    /**
     * @brief create_shoal create a shoal in the database with the information
     * @param s Shoal to put into database
     * @return 1 if successful, 0 if not
     */
    int create_shoal(Shoal* s);

private:
    db::ContentDB* db;
    user::AccountIO aio;

    /**
     * @brief next_id find the next highest id for a post
     * @return the next id that can be used for a post
     */
    int next_id();

    /**
     * @brief next_trade_id find the next highest id for a trade
     * @return the next id that can be used for a trade
     */
    int next_trade_id();

    /**
     * @brief next_survey_id find the next highest id for a survey
     * @return the next id that can be used for a survey
     */
    int next_survey_id();

    /**
     * @brief next_event_id find the next highest id for a event
     * @return the next id that can be used for a event
     */
    int next_event_id();
};

} // namespace content

#endif // CONTENT_POSTIO_H
