#include "account.h"

user::Account::Account() :
    id(-1), access(0), login_verified(0), guardianId(-1), username(""),
    email("") {}

user::Account::~Account() {}

user::Account::Account(std::string username, std::string email, int access) :
    id(-1), access(access), login_verified(0), guardianId(-1),
    username(username), email(email) {}

int user::Account::get_id() { return id; }
int user::Account::get_access() { return access; }
int user::Account::get_guardianId() { return guardianId; }
std::string user::Account::get_username() { return username; }
std::string user::Account::get_email() { return email; }
int user::Account::get_verified() { return login_verified; }

void user::Account::set_access(int a) {
    if (access == a) return;
    access = a;
    // editing the account object means this account no longer matches the db
    // so it is no longer verified
    login_verified = 0;
}

void user::Account::set_username(std::string u) {
    if (username == u) return;
    username = u;
    login_verified = 0;
}

void user::Account::set_email(std::string e) {
    if (email == e) return;
    email = e;
    login_verified = 0;
}

void user::Account::set_guardianId(int g) {
    if (guardianId == g) return;
    guardianId = g;
    login_verified = 0;
}
