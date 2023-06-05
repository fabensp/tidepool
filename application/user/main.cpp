#include <iostream>

#include "accountio.h"
#include "userconfig.h"
#include "gtest/gtest.h"

class AccountTest : public ::testing::Test {
protected:
    db::UserDB db;
    user::AccountIO aio;

    AccountTest() : db("../../database.sqlite"), aio(&db) {}

    virtual ~AccountTest() {}
};

class UserConfigTest : public ::testing::Test {
protected:
    db::UserDB db;
    user::AccountIO aio;
    user::UserConfig cfg;

    UserConfigTest() : db("../../database.sqlite"), aio(&db), cfg(&db) {}

    virtual ~UserConfigTest() {}
};

TEST_F(AccountTest, ACCOUNTIO_PULL) {
    user::Account a1, a2, a3;

    // Pulling Accounts without Verifying
    ASSERT_EQ(aio.pull(a1, 2), 1);
    ASSERT_EQ(a1.get_id(), 2);
    ASSERT_EQ(a1.get_username(), "PrlCtchr");
    ASSERT_EQ(a1.get_email(), "pearlcatcherfish@gmail.com");
    ASSERT_EQ(a1.get_access(), 32);
    ASSERT_EQ(a1.get_guardianId(), -1);
    ASSERT_EQ(a1.get_verified(), 0);

    ASSERT_EQ(aio.pull_username(a2, "PrlCtchr"), 1);
    ASSERT_EQ(a2.get_id(), 2);
    ASSERT_EQ(a2.get_username(), "PrlCtchr");
    ASSERT_EQ(a2.get_email(), "pearlcatcherfish@gmail.com");
    ASSERT_EQ(a2.get_access(), 32);
    ASSERT_EQ(a2.get_guardianId(), -1);
    ASSERT_EQ(a2.get_verified(), 0);

    ASSERT_EQ(aio.pull_email(a3, "pearlcatcherfish@gmail.com"), 1);
    ASSERT_EQ(a3.get_id(), 2);
    ASSERT_EQ(a3.get_username(), "PrlCtchr");
    ASSERT_EQ(a3.get_email(), "pearlcatcherfish@gmail.com");
    ASSERT_EQ(a3.get_access(), 32);
    ASSERT_EQ(a3.get_guardianId(), -1);
    ASSERT_EQ(a3.get_verified(), 0);
}

TEST_F(AccountTest, ACCOUNTIO_INSERT) {
    user::Account a1("sturgeot", "sturgeot@gmail.com", 0);

    ASSERT_EQ(aio.insert(a1, ""), 6); // fails because of bad email
    // NOTE: demonstrating aio.insert working would make change the database
    // such that tests would not be easily repeatable. it works, just trust me
}

TEST_F(AccountTest, ACCOUNTIO_UPDATE_BAN_UNAPPROVED) {
    user::Account a1, a2, a3;

    aio.pull(a1, 0);
    aio.pull(a2, 5);

    aio.verify(a1, "F1shApp!");

    // demonstrate update
    ASSERT_EQ(a2.get_username(), "PiranhaC"); // old name
    a2.set_username("newname");               // new name
    ASSERT_EQ(a2.get_username(), "newname");  // set new name locally
    ASSERT_EQ(aio.update(a2), 1);             // update db with new name
    aio.pull_username(a3, "newname");         // pull user with new name
    ASSERT_EQ(a2.get_id(), a3.get_id());      // assert they are the same user
    a2.set_username("PiranhaC");
    ASSERT_EQ(aio.update(a2), 1);

    // demonstrate ban
    ASSERT_EQ(aio.ban(5, a1), 1); // ban user 5 from a1 admin account
    aio.pull(a2, 5);
    ASSERT_EQ(a2.get_access(), 0);
    a2.set_access(2);
    aio.update(a2);

    // demonstrate unapproved
    std::vector<user::Account *> avec = aio.pull_unapproved();
    ASSERT_EQ((int)avec.size(), 0);
    a2.set_access(10); // 10 = 2 + 8, 2 for citizen and 8 for unapproved
    aio.update(a2);
    aio.pull(a3, 5);
    avec = aio.pull_unapproved();
    ASSERT_EQ((int)avec.size(), 1);
    ASSERT_EQ(avec.at(0)->get_id(), 5);
}

TEST_F(AccountTest, ACCOUNTIO_WRONGLOGIN) {
    // wrong username, access for the given email
    user::Account a1("peterf123", "sturgeot@gmail.com", 1);

    // Account Login Verification & Checking
    ASSERT_EQ(aio.verify(a1, "wrongpassword"), 0); // password wrong should fail
    ASSERT_EQ(a1.get_username(), "peterf123");     // no change if fails
    ASSERT_EQ(a1.get_access(), 1);
    ASSERT_EQ(aio.check(a1), 6);     // email/username taken but no id match
    ASSERT_EQ(a1.get_verified(), 0); // not verified yet
}

TEST_F(AccountTest, ACCOUNTIO_RIGHTLOGIN) {
    // wrong username, access for the given email
    user::Account a1("peterf123", "sturgeot@gmail.com", 1);

    ASSERT_EQ(aio.verify(a1, "F1shApp!"), 1); // correct password succeeds
    ASSERT_EQ(a1.get_username(), "sturgeot"); // overwrites incorrect info
    ASSERT_EQ(a1.get_access(), 64);
    ASSERT_EQ(a1.get_verified(), 1); // verified flag set true
    ASSERT_EQ(aio.check(a1), 1);     // succeed after verification
}

TEST_F(UserConfigTest, USERCONFIG_GET) {
    user::Account a1;
    user::Account a2;

    aio.pull(a1, 0);
    aio.pull(a2, 1);

    aio.verify(a1, "F1shApp!"); // only verify (log in) a1

    ASSERT_EQ(cfg.get_entry(a1, "theme"), 0);  // works right
    ASSERT_EQ(cfg.get_entry(a1, "wrong"), -1); // bad key err (from "wrong")
    ASSERT_EQ(cfg.get_entry(a2, "theme"), -2); // bad acct err (a2 not verified)
}

TEST_F(UserConfigTest, USERCONFIG_SET) {
    user::Account a1;
    user::Account a2;

    aio.pull(a1, 0);
    aio.pull(a2, 1);

    aio.verify(a1, "F1shApp!"); // only verify (log in) a1

    // works right with verified account
    ASSERT_EQ(cfg.set_entry(a1, "theme", 1), 1);
    ASSERT_EQ(cfg.get_entry(a1, "theme"), 1);
    ASSERT_EQ(cfg.set_entry(a1, "theme", 0), 1);
    ASSERT_EQ(cfg.get_entry(a1, "theme"), 0);

    // err (a2 not verified)
    ASSERT_EQ(cfg.set_entry(a2, "theme", 1), 0);

    // NOTE: demonstrating cfg.touch would make the database change
    // such that tests would not be easily repeatable. it works, just trust me
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
