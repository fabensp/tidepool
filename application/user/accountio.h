#ifndef USER_ACCOUNTIO_H
#define USER_ACCOUNTIO_H

#include "../database/userdb.h"
#include "account.h"

namespace user {

class AccountIO {
public:
    AccountIO();
    AccountIO(db::UserDB* db);

    /**
     * @brief db_pull gets user information from database by id
     * @param id user id # to get data from
     * @return 1 = success, 0 = fail
     */
    int pull(Account& a, int id);

    /**
     * @brief db_pull gets user information from database by username
     * @param username
     * @return 1 = success, 0 = fail
     */
    int pull_username(Account& a, std::string username);

    /**
     * @brief db_pull gets user information from database by email
     * @param email
     * @return 1 = success, 0 = fail
     */
    int pull_email(Account& a, std::string email);

    /**
     * @brief pull_unapproved constructs a vector of all users pending approval
     * @return vector of account objects
     * unapproved users have restrictions on their actions
     * and need admin approval to join the platform
     */
    std::vector<Account*> pull_unapproved();

    /**
     * @brief check checks whether a user already exists in the database
     * @param a Account to check
     * @return 1 = no issues, 0 = err, 2 = bad username, 4 = bad email
     * return can be any combination of 0, 2, 4.    8 = need guardian
     */
    int check(Account& a);

    /**
     * @brief db_insert inserts the User object's data into the database
     * @return 1 = no issues, 0 = err, 2 = bad username, 4 = bad email
     * return can be any combination of 0, 2, 4.    8 = need guardian
     */
    int insert(Account& a, std::string password);

    /**
     * @brief db_update updates database with User object's data
     * @return 1 = no issues, 0 = err, 2 = bad username, 4 = bad email
     * return can be any combination of 0, 2, 4.    8 = need guardian
     */
    int update(Account& a, std::string password = "");

    /**
     * @brief db_verify checks the database to validate login
     * @return 1 = success, 0 = fail
     */
    int verify(Account& a, std::string password);

    /**
     * @brief ban bans a user by setting their access to 0
     * @param id id of person to ban
     * @param a validated account of banning privileged user
     * @return success
     */
    int ban(int id, Account& a);

private:
    db::UserDB* db;

    /**
     * @brief db_next_id queries user database for the next sequential id slot
     * @return int id
     */
    int next_id();
};

} // namespace user

#endif // USER_ACCOUNTIO_H
