#ifndef USERCONFIG_H
#define USERCONFIG_H

#include "../database/userdb.h"
#include "account.h"

namespace user {

class UserConfig {
public:
    UserConfig();
    UserConfig(db::UserDB* db);

    /**
     * @brief get_entry returns the value of a certain config option
     * @param a account to get setting from. must be a login verified account
     * @param key text name of attribute to get
     * @return config attribute value or error code. -1 = bad key, -2 = bad acct
     * account must be verified
     */
    int get_entry(Account& a, std::string key);

    /**
     * @brief set_entry sets a user's setting
     * @param a account to get setting from. must be a login verified account
     * @param key
     * @param val
     * @return success = 1, fail = 0
     * keys: "menu" "landing" "top" "bottom" "theme"
     * vals:  0-1    0-3       0-5   0-5      0-7
     * account must be verified
     */
    int set_entry(Account& a, std::string key, int val);

    /**
     * @brief touch_cfg creates entry w/ default vals or does nothing if exists
     * @param a account to check
     * @return success = 1, fail = 0
     * account must be verified
     */
    int touch_cfg(Account& a);

private:
    db::UserDB* db;
};

} // namespace user

#endif // USERCONFIG_H
