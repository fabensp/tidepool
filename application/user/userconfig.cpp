#include "userconfig.h"

user::UserConfig::UserConfig(db::UserDB* db) : db(db) {}

int user::UserConfig::get_entry(Account& a, std::string key) {
    if (!a.get_verified()) return -2; // can't pull cfg for users besides curr
    db->fetch_cfg(a.get_id(), key);
    if (db->next())
        return db->result()->value(QString::fromStdString(key)).toInt();
    return -1;
}

int user::UserConfig::set_entry(Account& a, std::string key, int val) {
    if (!a.get_verified()) return 0;
    db->update_cfg(a.get_id(), key, val);
    return 1;
}

int user::UserConfig::touch_cfg(Account& a) {
    if (!a.get_verified()) return 0;
    db->touch_cfg(a.get_id());
    return 1;
}
