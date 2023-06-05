#ifndef CHATIO_H
#define CHATIO_H
#include "message.h"
#include "chat.h"
#include <vector>
#include "../user/accountio.h"
#include "../database/chatdb.h"

namespace chat {

class ChatIO
{

    friend class ChatIOTest;

public:
    /**
     * @brief Constructor that links to the chat database
    */
    ChatIO(db::ChatDB* db);

    /**
     * @brief update_chat Update the theme and title of an existing chat
     * @param c Chat to be updated
     * @param title New title
     * @param theme New theme
     * @returns 1 if successful, 0 if not
    */
    int update_chat(chat::Chat& c, std::string title, int theme);

    /**
     * @brief add_member Add a user to a chat
     * @param c Chat to add user to
     * @param u User to add to chat
     * @returns 1 if successful, 0 if not
    */
    int add_member(Chat& c, user::Account* u);

    /**
     * @brief add_member Add a user to a chat by their username
     * @param c Chat to add user to
     * @param u Username of user to add to chat
     * @returns 1 if successful, 0 if not
    */
    int add_member(Chat& c, std::string u);

    /**
     * @brief remove_member Remove a user from a chat
     * @param c Chat to remove user from
     * @param u User to remove from chat
     * @returns 1 if successful, 0 if not
    */
    int remove_member(Chat& c, user::Account* u);

    /**
     * @brief pull_chats Pull all the chats of a user from the database
     * @param u User to pull chats from
     * @returns a vector of chats
    */
    vector<Chat*> pull_chats(user::Account* u);

    /**
     * @brief pull_num_chats Pull a given number of users chats
     * @param a Users account to pull chats of
     * @param n Number of chats to pull
     * @return A vector of the users chats
     */
    vector<Chat*> pull_num_chats(user::Account* u, int n);

    /**
     * @brief new_message Create a new message in a chat
     * @param c       Chat to inpur message into
     * @param message The message to send
     * @param u       The sender of the message
     * @return 1 if successful, 0 if not
     */
    int new_message(Chat& c, string message, user::Account* u);

    /**
     * @brief pull_message puts all messages in to the chats msg vector
     * @param m  Message to push into
     * @param id message identifier
     * @return 1 if succesful, 0 if not
     */
    int pull_message(Message& m, int id);

    /**
     * @brief pull_num_messages puts n messages in to the chat c's msg vector
     * @param c chat to get msgs for and put in to
     * @param n num msgs to get
     * @return 1 if successful, 0 if not
     */
    int pull_num_messages(Chat& c, int n);

    /**
     * @brief create_chat create a new chat
     * @param c Chat to creat into
     * @return 1 if succesful, 0 if not
     */
    int create_chat(Chat& c);

    /**
     * @brief set_read Set the read value of a chat for a user
     * @param c Chat to set as read
     * @param u user who it is read for
     * @return 1 if successful, 0 if not
     */
    int set_read(Chat& c, user::Account* u);

    /**
     * @brief set_unread Set the read value of a chat for a user to be unread
     * @param c Chat to set as unread
     * @param u user who it is unread for
     * @return 1 if successful, 0 if not
     */
    int set_unread(Chat& c);

    /**
     * @brief pull_chat pulls a chat with a given chat id
     * @param c chat to push into
     * @param chatId identifier of the wanted chat
     * @return 1 if successful, 0 if not
     */
    int pull_chat(Chat& c, int chatId);

    /**
     * @brief remove_message removes a message from the structure
     * @param m Message to remove
     * @param admin Admin account that authorized the removal
     * @return 1 if successful, 0 if not
     */
    int remove_message(chat::Message& m, user::Account& admin);

    /**
     * @brief remove_chat removes a chat from the structure
     * @param c Chat to remove
     * @return 1 if successful, 0 if not
     */
    int remove_chat(chat::Chat& c);

    /**
     * @brief pull_chat_members pulls all the members of a given chat
     * @param c Chat to find members of
     * @return a vector of users whos are in the chat
     */
    std::vector<user::Account*> pull_chat_members(Chat& c);

private:
    db::ChatDB* db;
    user::AccountIO aio;

    /**
     * @brief next_id finds the next id to use for a new chat
     * @return next id
     */
    int next_id();

    /**
     * @brief next_messageId finds the next id to use for a message
     * @return next id
     */
    int next_messageId();

};
}

#endif // CHATIO_H
