#include "chatio.h"

/**
 * @brief Constructor that links to the chat database
*/
chat::ChatIO::ChatIO(db::ChatDB* db) : db(db), aio((db::UserDB*)db) {}

/**
 * @brief update_chat Update the theme and title of an existing chat
 * @param c     Chat to be updated
 * @param title New title
 * @param theme New theme
 * @returns 1 if successful, 0 if not
*/
int chat::ChatIO::update_chat(chat::Chat& c, std::string title, int theme) {
    if (c.id < 0) return 0;
    db->fetch_chat(c.id);
    if (db->next()) {
        db->update_chat(c.id, title, theme);
        c.theme = theme;
        c.title = title;
        return 1;
    }
    return 0;
}

/**
 * @brief add_member Add a user to a chat
 * @param c Chat to add user to
 * @param u User to add to chat
 * @returns 1 if successful, 0 if not
*/
int chat::ChatIO::add_member(chat::Chat& c, user::Account* u) {
    // Make sure the accounts exist
    if (u->get_id() == -1) return 0;
    if (c.id < 0) return 0;
    db->fetch_chat(c.id);
    if (db->next()) {
        db->create_chat_membership(c.id, u->get_id());
        return 1;
    }
    return 0;
}

/**
 * @brief add_member Add a user to a chat by their username
 * @param c Chat to add user to
 * @param u Username of user to add to chat
 * @returns 1 if successful, 0 if not
*/
int chat::ChatIO::add_member(chat::Chat& c, std::string u) {
    // Make sure the accounts exist
    if (u == "") return 0;
    if (c.id < 0) return 0;
    db->fetch_chat(c.id);
    if (db->next()) {
        db->create_chat_membership(c.id, u);
        return 1;
    }
    return 0;
}

/**
 * @brief remove_member Remove a user from a chat
 * @param c Chat to remove user from
 * @param u User to remove from chat
 * @returns 1 if successful, 0 if not
*/
int chat::ChatIO::remove_member(Chat& c, user::Account* u) {
    // Make sure the accounts exist
    if (u->get_id() == -1) return 0;
    if (c.id < 0) return 0;
    db->fetch_chat(c.id);
    if (db->next()) {
        db->remove_chat_membership(c.id, u->get_id());
        return 1;
    }
    return 0;
}

/**
 * @brief pull_chats Pull all the chats of a user from the database
 * @param u User to pull chats from
 * @returns a vector of chats
*/
vector<chat::Chat*> chat::ChatIO::pull_chats(user::Account* u) {
    vector<Chat*> out;
    if (u->get_id() == -1) return out;
    db->fetch_all_chats(u->get_id());
    while (db->next()) {
        Chat* c = new Chat;
        c->id = db->result()->value("id").toInt();
        c->theme = db->result()->value("theme").toInt();
        c->title = db->result()->value("title").toString().toStdString();
        out.push_back(c);
    }
    return out;
}

/**
 * @brief pull_num_chats Pull a given number of users chats
 * @param a Users account to pull chats of
 * @param n Number of chats to pull
 * @return  A vector of the users chats
 */
vector<chat::Chat*> chat::ChatIO::pull_num_chats(user::Account* a, int n) {
    vector<Chat*> out;
    if (a->get_id() < 0) return out;
    db->fetch_num_chats(a->get_id(), n);
    while (db->next()) {
        Chat* c = new Chat;
        c->id = db->result()->value("id").toInt();
        c->theme = db->result()->value("theme").toInt();
        c->title = db->result()->value("title").toString().toStdString();
        c->unread = db->result()->value("unread").toInt();
        out.push_back(c);
    }
    return out;
}

/**
 * @brief new_message Create a new message in a chat
 * @param c       Chat to inpur message into
 * @param message The message to send
 * @param u       The sender of the message
 * @returns 1 if successful, 0 if not
 */
int chat::ChatIO::new_message(chat::Chat& c, string message, user::Account* u) {
    if (u->get_id() == -1) return 0;
    db->fetch_chat(c.id);
    if (db->next()) {
        db->insert_message(next_messageId(), u->get_id(), c.id, message);
        return 1;
    }
    return 0;
}

/**
 * @brief pull_message puts all messages in to the chats msg vector
 * @param m  Message to push into
 * @param id message identifier
 * @return 1 if succesful, 0 if not
 */
int chat::ChatIO::pull_message(chat::Message& m, int id) {
    if (id < 0) return 0;
    db->pull_message(id);
    int user_id = 0;
    if (db->next()) {
        user_id = db->result()->value(0).toInt();
        m.message = db->result()->value(1).toString().toStdString();
        m.timestamp = db->result()->value(2).toString().toStdString();
    }
    user::Account a;
    aio.pull(a, user_id);
    m.sender = a;
    m.id = id;
    return 1;
}

/**
 * @brief pull_num_messages puts n messages in to the chat c's msg vector
 * @param c chat to get msgs for and put in to
 * @param n num msgs to get
 * @return 1 if successful, 0 if not
 */
int chat::ChatIO::pull_num_messages(chat::Chat& c, int n) {
    if (c.id < 0) return 0;
    c.messages.clear();
    db->pull_num_chat_messages(c.id, n);
    std::vector<int> ids;
    while (db->next()) {
        chat::Message* m = new Message();
        ids.push_back(db->result()->value(0).toInt());
        m->message = db->result()->value(1).toString().toStdString();
        m->id = db->result()->value(2).toInt();
        m->timestamp = db->result()->value(3).toString().toStdString();
        c.messages.push_back(m);
    }
    int i = 0;
    for (Message* m : c.messages) {
        user::Account a;
        if (aio.pull(a, ids[i++])) m->sender = a;
        else m->sender.set_username("ERR");
    }
    return 1;
}

/**
 * @brief create_chat create a new chat
 * @param c Chat to creat into
 * @return 1 if succesful, 0 if not
 */
int chat::ChatIO::create_chat(Chat& c) {
    int id = next_id();
    db->insert_chat(id, c.theme, c.title);
    c.id = id;
    c.theme = 0;
    c.title = "New Chat";
    return 1;
}

/**
 * @brief set_read Set the read value of a chat for a user
 * @param c Chat to set as read
 * @param u user who it is read for
 * @return 1 if successful, 0 if not
 */
int chat::ChatIO::set_read(Chat& c, user::Account* u) {
    db->set_read(c.id, u->get_id());
    return 1;
}

/**
 * @brief set_unread Set the read value of a chat for a user to be unread
 * @param c Chat to set as unread
 * @param u user who it is unread for
 * @return 1 if successful, 0 if not
 */
int chat::ChatIO::set_unread(Chat& c) {
    db->set_unread(c.id);
    return 1;
}

/**
 * @brief pull_chat pulls a chat with a given chat id
 * @param c chat to push into
 * @param chatId identifier of the wanted chat
 * @return 1 if successful, 0 if not
 */
int chat::ChatIO::pull_chat(chat::Chat& c, int chatId) {
    if (chatId < 0) return 0;
    db->fetch_chat(chatId);
    if (db->next()) {
        c.id = chatId;
        c.theme = db->result()->value("theme").toInt();
        c.title = db->result()->value("title").toString().toStdString();
        return 1;
    }
    return 0;
}

/**
 * @brief remove_message removes a message from the structure
 * @param m Message to remove
 * @param admin Admin account that authorized the removal
 * @return 1 if successful, 0 if not
 */
int chat::ChatIO::remove_message(chat::Message& m, user::Account& admin) {
    if (admin.get_access() < 32 || !admin.get_verified()) return 0;
    db->remove_message(m.get_id());
    return 1;
}

/**
 * @brief remove_chat removes a chat from the structure
 * @param c Chat to remove
 * @return 1 if successful, 0 if not
 */
int chat::ChatIO::remove_chat(chat::Chat& c) {
    db->remove_chat(c.get_id());
    return 1;
}

/**
 * @brief pull_chat_members pulls all the members of a given chat
 * @param c Chat to find members of
 * @return a vector of users whos are in the chat
 */
std::vector<user::Account*> chat::ChatIO::pull_chat_members(Chat& c) {
    std::vector<user::Account*> out;
    if (c.id < 0) return out;
    db->fetch_chat_members(c.id);
    std::vector<int> ids;
    while (db->next()) {
        ids.push_back(db->result()->value(0).toInt());
        out.push_back(new user::Account());
    }
    int i = 0;
    for (user::Account* a : out) aio.pull(*a, ids[i++]);
    return out;
}

/**
 * @brief next_id finds the next id to use for a new chat
 * @return next id
 */
int chat::ChatIO::next_id() {
    db->max_chatId();
    // "SELECT MAX(id) from chat;"
    int num;
    if (db->next()) {
        num = db->result()->value("Max(id)").toInt();
    } else return -100;
    int id = num + 1;
    return id;
}

/**
 * @brief next_messageId finds the next id to use for a message
 * @return next id
 */
int chat::ChatIO::next_messageId() {
    db->max_messageId();
    // "SELECT MAX(id) from chat;"
    int num;
    if (db->next()) {
        num = db->result()->value("Max(id)").toInt();
    } else return -100;
    int id = num + 1;
    return id;
}
