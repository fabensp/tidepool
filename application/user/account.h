#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

namespace user {

class Account {

    friend class AccountIO;

public:
    Account();
    Account(std::string email, std::string username = "", int access = -1);

    ~Account();

    int get_id();
    int get_access();
    int get_guardianId();
    std::string get_username();
    std::string get_email();

    void set_access(int a);
    void set_username(std::string u);
    void set_email(std::string e);
    void set_guardianId(int id);

    /**
     * @brief get_verified returns whether this Account has correct information
     * @return 0 = unverified, 1 = verified
     */
    int get_verified();

private:
    int id;
    int access;
    int login_verified;
    int guardianId;
    std::string username;
    std::string email;
};

} // namespace user
#endif // ACCOUNT_H
