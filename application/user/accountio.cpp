#include "accountio.h"

namespace user {

AccountIO::AccountIO() {}

AccountIO::AccountIO(db::UserDB* db) : db(db) {}

int user::AccountIO::pull(Account& a, int id) {
    if (id < 0) return 0; // id under 0 is impossible
    db->fetch_user(id);
    if (db->next()) {
        a.username = db->result()->value("username").toString().toStdString();
        a.email = db->result()->value("email").toString().toStdString();
        a.access = db->result()->value("access").toInt();
    } else return 0;
    if ((a.access & 1) == 1) { // test if underage
        db->fetch_guardian(id);
        if (db->next())
            a.guardianId = db->result()->value("guardian_id").toInt();
        else return 0;
    }
    a.id = id;
    a.login_verified = 0;
    return 1;
}

int user::AccountIO::pull_username(Account& a, std::string username) {
    if (username == "") return 0;
    db->fetch_user_username(username);
    if (db->next()) {
        a.id = db->result()->value("id").toInt();
        a.email = db->result()->value("email").toString().toStdString();
        a.access = db->result()->value("access").toInt();
    } else return 0;
    if ((a.access & 1) == 1) { // test if underage
        db->fetch_guardian(a.id);
        if (db->next())
            a.guardianId = db->result()->value("guardian_id").toInt();
        else return 0;
    }
    a.username = username;
    a.login_verified = 0;
    return 1;
}

int user::AccountIO::pull_email(Account& a, std::string email) {
    if (email == "") return 0;
    db->fetch_user_email(email);
    if (db->next()) {
        a.id = db->result()->value("id").toInt();
        a.username = db->result()->value("username").toString().toStdString();
        a.access = db->result()->value("access").toInt();
    } else return 0;
    if ((a.access & 1) == 1) { // test if underage
        db->fetch_guardian(a.id);
        if (db->next())
            a.guardianId = db->result()->value("guardian_id").toInt();
        else return 0;
    }
    a.email = email;
    a.login_verified = 0;
    return 1;
}

std::vector<user::Account*> user::AccountIO::pull_unapproved() {
    db->fetch_unapproved();
    std::vector<user::Account*> out;
    while (db->next()) {
        Account* a = new Account();
        pull(*a, db->result()->value(0).toInt());
        if (a->id != -1) out.push_back(a);
        else delete a;
    }
    return out;
}

int user::AccountIO::check(Account& a) {
    int query_result = 1;
    db->check_user(a.username, a.email, a.id);
    if (db->next()) {
        query_result += 2 * db->result()->value(0).toInt();
        query_result += 4 * db->result()->value(1).toInt();
    } else return 0;
    if (query_result > 1) query_result--;
    return query_result;
}

int user::AccountIO::insert(Account& a, std::string password) {
    int chk = check(a);
    if (chk != 1) return chk;
    int id = next_id();
    // test if underage and has guardian
    if ((a.access & 1) == 1) {
        db->check_guardian(a.guardianId);
        db->next();
        if (!db->result()->value(0).toInt() || !db->result()->isValid())
            return 8;
    }
    db->insert_user(id, a.username, a.email, password, a.access);
    if ((a.access & 1) == 1) db->insert_guardian(a.id, a.guardianId);
    a.id = id;
    verify(a, password);
    return 1;
}

int user::AccountIO::update(Account& a, std::string password) {
    int chk = check(a);
    if (a.id < 0) return 0;
    if (chk != 1) return chk;
    // test if underage and has guardian
    if ((a.access & 1) == 1 && a.guardianId > -1) {
        db->fetch_guardian(a.id);
        if (db->next()) db->update_guardian(a.id, a.guardianId);
        else db->insert_guardian(a.id, a.guardianId);
    } else if ((a.access & 1) == 1) return 8;
    db->update_user(a.id, a.username, a.email, password, a.access);
    return 1;
}

int user::AccountIO::verify(Account& a, std::string password) {
    db->verify_user(a.email, password);
    if (db->next()) {
        a.id = db->result()->value("id").toInt();
        a.username = db->result()->value("username").toString().toStdString();
        a.access = db->result()->value("access").toInt();
        a.login_verified = 1;
    } else return 0;
    return 1;
}

int user::AccountIO::next_id() {
    db->max_userid();
    int num;
    if (db->next()) {
        num = db->result()->value("MAX(id)").toInt();
    } else return -100;
    int id = num + 1;
    return id;
}

int user::AccountIO::ban(int id, user::Account& admin) {
    if (admin.get_access() < 32 || !admin.get_verified()) return 0;
    Account a;
    pull(a, id);
    db->update_user(a.id, a.username, a.email, "", 0);
    return 1;
}

} // namespace user
