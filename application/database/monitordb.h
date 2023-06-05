#ifndef DB_MONITORDB_H
#define DB_MONITORDB_H

#include "database.h"
#include <string>

namespace db {

/**
 * @brief The MonitorDB class provides functionality to interact with the monitoring-related tables in the database.
 */
class MonitorDB : public Database {
public:
    /**
     * @brief Constructs a MonitorDB object with the specified database file.
     * @param file The database file name.
     */
    MonitorDB(std::string file);

    /**
     * @brief Fetches posts from the database based on the specified filter and search criteria using equijoin.
     * @param filter The filter to apply to the query.
     * @param search The search criteria to apply to the query.
     * @param r The number of results to fetch (optional, default: 1).
     */
    void fetch_posts_equijoined(QString filter, QString search, int r = 1);

    /**
     * @brief Fetches messages from the database based on the specified filter and search criteria using equijoin.
     * @param filter The filter to apply to the query.
     * @param search The search criteria to apply to the query.
     * @param r The number of results to fetch (optional, default: 1).
     */
    void fetch_messages_equijoined(QString filter, QString search, int r = 1);

    /**
     * @brief Fetches profiles from the database based on the specified filter and search criteria using equijoin.
     * @param filter The filter to apply to the query.
     * @param search The search criteria to apply to the query.
     * @param r The number of results to fetch (optional, default: 1).
     */
    void fetch_profiles_equijoined(QString filter, QString search, int r = 1);

    /**
     * @brief Reports a post to the system.
     * @param postId The ID of the post to report.
     * @param reporterId The ID of the user reporting the post.
     */
    void report_post(int postId, int reporterId);

    /**
     * @brief Reports a message to the system.
     * @param messageId The ID of the message to report.
     * @param reporterId The ID of the user reporting the message.
     */
    void report_message(int messageId, int reporterId);

    /**
     * @brief Reports a profile to the system.
     * @param toId The ID of the user whose profile is being reported.
     * @param fromId The ID of the user reporting the profile.
     */
    void report_profile(int toId, int fromId);

    /**
     * @brief Removes the report on a post.
     * @param postId The ID of the post to unreport.
     */
    void unreport_post(int postId);

    /**
     * @brief Removes the report on a message.
     * @param messageId The ID of the message to unreport.
     */
    void unreport_message(int messageId);

    /**
     * @brief Removes the report on a profile.
     * @param toId The ID of the user whose profile is being unreported.
     */
    void unreport_profile(int toId);
};

} // namespace db

#endif // DB_MONITORDB_H
