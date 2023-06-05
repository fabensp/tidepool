
#ifndef DB_CONTENTDB_H
#define DB_CONTENTDB_H

#include "database.h"

namespace db {

/**
 * @brief The ContentDB class provides functionality to interact with the content-related tables in the database.
 */
class ContentDB : public Database {
public:
    /**
         * @brief Constructs a ContentDB object with the specified database file.
         * @param file The database file name.
         */
    ContentDB(std::string file) : Database(file) {}

    /**
         * @brief Fetches the details of a specific post.
         * @param postId The ID of the post.
         */
    void fetch_post(int postId);

    /**
         * @brief Fetches the details of a specific trade.
         * @param id The ID of the trade.
         */
    void fetch_trade(int id);

    /**
         * @brief Fetches the details of a specific survey.
         * @param id The ID of the survey.
         */
    void fetch_survey(int id);

    /**
         * @brief Fetches the details of a specific event.
         * @param id The ID of the event.
         */
    void fetch_event(int id);

    /**
         * @brief Inserts a new post into the database.
         * @param id The ID of the post.
         * @param creator_id The ID of the post creator.
         * @param shoal_tag The tag of the shoal the post belongs to.
         * @param message The content of the post.
         * @param iid The ID of the image associated with the post (optional).
         * @param tid The ID of the trade associated with the post (optional).
         * @param sid The ID of the survey associated with the post (optional).
         * @param eid The ID of the event associated with the post (optional).
         */
    void insert_post(int id, int creator_id, std::string shoal_tag,
                     std::string message, int iid, int tid, int sid, int eid);

    /**
         * @brief Removes a post from the database.
         * @param id The ID of the post.
         */
    void remove_post(int id);

    /**
         * @brief Fetches the details of a specific shoal.
         * @param tag The tag of the shoal.
         */
    void fetch_shoal(std::string tag);

    /**
         * @brief Fetches the shoals associated with a specific user.
         * @param id The ID of the user.
         */
    void fetch_user_shoals(int id);

    /**
         * @brief Pulls a specific number of posts from the reef of a user.
         * @param userId The ID of the user.
         * @param n The number of posts to fetch.
         * @param offset The offset for pagination (optional, default: 0).
         */
    void pull_num_reef_posts(int userId, int n, int offset = 0);

    /**
         * @brief Pulls a specific number of posts from a specific user shoal.
         * @param userId The ID of the user.
         * @param n The number of posts to fetch.
         * @param offset The offset for pagination (optional, default: 0).
         */
    void pull_num_user_shoal_posts(int userId, int n, int offset = 0);

    /**
         * @brief Pulls a specific number of posts from a specific shoal.
         * @param tag The tag of the shoal.
         * @param n The number of posts to fetch.
         * @param offset The offset for pagination (optional, default: 0).
         */
    void pull_num_shoal_posts(std::string tag, int n, int offset = 0);

    /**
         * @brief Pulls a specific number of posts from a specific user.
         * @param userId The ID of the user.
         * @param n The number of posts to fetch.
         * @param offset The offset for pagination (optional, default: 0).
         */
    void pull_num_user_posts(int userId, int n, int offset = 0);

    /**
        * @brief Inserts a new trade into the database.
        * @param id The ID of the trade.
        * @param pal_offer_id The ID of the offering pal.
        * @param offer_alt The alternative offer description.
        * @param pal_seek_id The ID of the seeking pal.
        * @param seek_alt The alternative seek description.
        */
    void insert_trade(int id, int pal_offer_id, std::string offer_alt, int pal_seek_id, std::string seek_alt);

    /**
         * @brief Inserts a new survey into the database.
         * @param id The ID of the survey.
         * @param opt1msg The message for option 1.
         * @param opt2msg The message for option 2.
         * @param opt3msg The message for option 3.
         * @param opt4msg The message for option 4.
         */
    void insert_survey(int id, std::string opt1msg, std::string opt2msg, std::string opt3msg, std::string opt4msg);

    /**
        * @brief Inserts a new event into the database.
        * @param id The ID of the event.
        * @param title The title of the event.
        * @param start The start date of the event.
        * @param end The end date of the event.
        * @param link_label The label for the event link.
        * @param link The link for the event.
        */
    void insert_event(int id, std::string title, std::string start, std::string end, std::string link_label, std::string link);

    /**
         * @brief Retrieves the maximum post ID from the database.
         */
    void max_postid();

    /**
         * @brief Retrieves the maximum trade ID from the database.
         */
    void max_tradeid();

    /**
         * @brief Retrieves the maximum survey ID from the database.
         */
    void max_surveyid();

    /**
       * @brief Retrieves the maximum event ID from the database.
       */
    void max_eventid();

    /**
         * @brief Creates a new shoal in the database.
         * @param tag The tag of the shoal.
         * @param theme The theme of the shoal.
         * @param desc The description of the shoal.
         * @param cid The ID of the creator.
         */
    void create_shoal(std::string tag, int theme, std::string desc, int cid);
};

} // namespace db

#endif // DB_CONTENTDB_H
