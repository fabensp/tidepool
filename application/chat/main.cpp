#include "chatio.h"
#include "gtest/gtest.h"
#include <iostream>

class ChatTest : public ::testing::Test {
protected:
    db::ChatDB db;
    chat::ChatIO cio;

    ChatTest() : db("../../database.sqlite"), cio(&db) {}

    virtual ~ChatTest() {}
};

class ChatIOTest : public ::testing::Test {

protected:
    ChatIOTest() : db("../../database.sqlite"), cio((db::ChatDB*)&db), aio((db::UserDB*)&db) {}

    virtual ~ChatIOTest() {}
    int i;
    db::Database db;
    chat::ChatIO cio;
    user::AccountIO aio;
};

TEST_F(ChatIOTest, CIO_GENERAL_TESTS) {
    chat::Message m;
    ASSERT_EQ(cio.pull_message(m, 1), 1);
    ASSERT_EQ(m.get_id(), 1);
    ASSERT_EQ(m.get_content(), "Hey guys, how's everyone doing?");
    ASSERT_EQ(m.get_timestamp(), "01/01/2017");

    chat::Message m2;
    cio.pull_message(m2, 2);
    ASSERT_EQ(m2.get_id(), 2);
    ASSERT_EQ(m2.get_content(), "Can someone help me figure out why my fish are dying?");
    ASSERT_EQ(m2.get_timestamp(), "01/02/2017");

    //Test pulling a chat
    chat::Chat c;
    cio.pull_chat(c, 1);
    ASSERT_EQ(c.get_id(), 1);
    ASSERT_EQ(c.get_theme(), 0);
    ASSERT_EQ(c.get_title(), "Fish talk");

    //Test creating a chat
    chat::Chat c1;
    cio.create_chat(c1);
    ASSERT_EQ(c1.get_id(), 9);
    ASSERT_EQ(c1.get_theme(), 0);
    ASSERT_EQ(c1.get_title(), "New Chat");

    //Test adding a member to the chat
    user::Account a;
    aio.pull(a, 0);
    ASSERT_EQ(cio.add_member(c, &a), 1);

    //Test sending a message
    ASSERT_EQ(cio.new_message(c, "hello there everyone", &a), 1);
    ASSERT_EQ(cio.pull_num_messages(c, 10), 1);
    std::vector<chat::Message *> mvec = c.get_messages();
    ASSERT_EQ(mvec.size(), 10);

    // Test updating a chat
    ASSERT_EQ(cio.update_chat(c, "chatty chat chat", 1), 1);
    ASSERT_EQ(c.get_title(), "chatty chat chat");
    ASSERT_EQ(c.get_theme(), 1);
    cio.update_chat(c, "Fish talk", 0);

    //Test pulling a users chats
    std::vector<chat::Chat *> chats = cio.pull_chats(&a);
    ASSERT_EQ(chats.size(), 27);

    //Test removing a member
    ASSERT_EQ(cio.remove_member(c, &a), 1);
}

TEST_F(ChatIOTest, CIO_PULL_NUM_MESSAGES) {
    chat::Chat c;
    ASSERT_EQ(cio.pull_chat(c, 1), 1);
    ASSERT_EQ(cio.pull_num_messages(c, 10), 1);
    ASSERT_EQ(c.get_id(), 1);
    ASSERT_EQ(c.get_title(), "Fish talk");
    std::vector<chat::Message *> mvec = c.get_messages();
    ASSERT_EQ(mvec.size(), 10);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
