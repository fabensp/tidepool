#ifndef USERDB_H
#define USERDB_H

#include "database.h"
#include <string>

namespace db {

/**
 * @brief The UserDB class provides functionality to interact with the user-related tables in the database.
 */
class UserDB : public Database {
public:
    /**
         * @brief Constructs a UserDB object with the specified database file.
         * @param file The database file name.
         */
    UserDB(std::string file);

    // AccountIO Methods

    /**
         * @brief Fetches the details of a specific user from the database.
         * @param id The ID of the user to fetch.
         */
    void fetch_user(int id);

    /**
         * @brief Fetches the details of a specific user based on the username from the database.
         * @param username The username of the user to fetch.
         */
    void fetch_user_username(std::string username);

    /**
         * @brief Fetches the details of a specific user based on the email from the database.
         * @param email The email address of the user to fetch.
         */
    void fetch_user_email(std::string email);

    /**
         * @brief Fetches the guardian details for a specific user from the database.
         * @param id The ID of the user to fetch the guardian for.
         */
    void fetch_guardian(int id);

    /**
         * @brief Fetches the details of unapproved users from the database.
         */
    void fetch_unapproved();

    /**
         * @brief Checks if the username and email are available for a new user or an existing user in the database.
         * @param username The username to check.
         * @param email The email address to check.
         * @param id The ID of an existing user to exclude from the check (optional).
         */
    void check_user(std::string username, std::string email, int id);

    /**
         * @brief Inserts a new user into the database.
         * @param id The ID of the user.
         * @param username The username of the user.
         * @param email The email address of the user.
         * @param password The password of the user.
         * @param access The access level of the user.
         */
    void insert_user(int id, std::string username, std::string email, std::string password, int access);

    /**
         * @brief Updates the details of a user in the database.
         * @param id The ID of the user.
         * @param username The new username of the user.
         * @param email The new email address of the user.
         * @param password The new password of the user (optional).
         * @param access The new access level of the user (optional).
         */
    void update_user(int id, std::string username, std::string email, std::string password = "", int access = -1);

    /**
         * @brief Verifies the email and password of a user for authentication.
         * @param email The email address of the user.
         * @param password The password of the user.
         */
    void verify_user(std::string email, std::string password);

    /**
         * @brief Inserts a guardian-child relationship in the database.
         * @param childId The ID of the child user.
         * @param guardianId The ID of the guardian user.
         */
    void insert_guardian(int childId, int guardianId);

    /**
             * @brief Updates the guardian of a user in the database.
             * @param id The ID of the user.
             * @param guardianId The new guardian ID
              */
    void update_guardian(int id, int guardianId);

    /**
         * @brief Checks if a user has a guardian in the database.
         * @param id The ID of the user.
         */
    void check_guardian(int id);

    /**
        * @brief Retrieves the maximum user ID from the database.
        */
    void max_userid();

    // UserConfig Methods

    /**
         * @brief Fetches the configuration value for a specific user and key from the database.
         * @param userId The ID of the user.
         * @param key The configuration key.
         */
    void fetch_cfg(int userId, std::string key);

    /**
         * @brief Updates the configuration value for a specific user and key in the database.
         * @param userId The ID of the user.
         * @param key The configuration key.
         * @param val The new configuration value.
         */
    void update_cfg(int userId, std::string key, int val);

    /**
         * @brief Updates the last modified timestamp for a specific configuration in the database.
         * @param id The ID of the configuration.
         */
    void touch_cfg(int id);
};

} // namespace db

#endif // USERDB_H
