#ifndef CHATDB_H
#define CHATDB_H

#include "database.h"
#include <string>

namespace db {

class ChatDB : public Database {
public:
    /**
         * @brief Constructs a ChatDB object with the specified database file.
         * @param file The database file name.
         */
    ChatDB(std::string file);

    /**
         * @brief Fetches the details of a specific chat.
         * @param chatId The ID of the chat.
         */
    void fetch_chat(int chatId);

    /**
         * @brief Fetches the members of a specific chat.
         * @param chatId The ID of the chat.
         */
    void fetch_chat_members(int chatId);

    /**
        * @brief Updates the details of a specific chat.
        * @param chatId The ID of the chat.
        * @param title The new title of the chat.
        * @param theme The new theme of the chat.
        */
    void update_chat(int chatId, std::string title, int theme);

    /**
         * @brief Creates a membership for a user in a specific chat.
         * @param chat_id The ID of the chat.
         * @param member_id The ID of the member.
         */
    void create_chat_membership(int chat_id, int member_id);

    /**
         * @brief Creates a membership for a user in a specific chat.
         * @param chat_id The ID of the chat.
         * @param member The username of the member.
         */
    void create_chat_membership(int chat_id, std::string member);

    /**
        * @brief Removes a membership of a user from a specific chat.
        * @param chatId The ID of the chat.
        * @param userId The ID of the user.
        */
    void remove_chat_membership(int chatId, int userId);

    /**
        * @brief Fetches all chats associated with a specific user.
        * @param user_id The ID of the user.
        */
    void fetch_all_chats(int user_id);

    /**
       * @brief Fetches a specific number of chats associated with a user.
       * @param userId The ID of the user.
       * @param n The number of chats to fetch.
       */
    void fetch_num_chats(int userId, int n);

    /**
        * @brief Inserts a new message into a chat.
        * @param id The ID of the message.
        * @param userId The ID of the user who sent the message.
        * @param chatId The ID of the chat.
        * @param message The message content.
        */
    void insert_message(int id, int userId, int chatId, std::string message);

    /**
         * @brief Removes a message from a chat.
         * @param id The ID of the message.
         */
    void remove_message(int id);

    /**
         * @brief Inserts a new chat into the database.
         * @param userId The ID of the user who created the chat.
         * @param theme The theme of the chat.
         * @param title The title of the chat.
         */
    void insert_chat(int userId, int theme, std::string title);

    /**
         * @brief Removes a chat from the database.
         * @param id The ID of the chat.
         */
    void remove_chat(int id);

    /**
         * @brief Pulls a specific message from the database.
         * @param msgId The ID of the message.
         */
    void pull_message(int msgId);

    /**
        * @brief Pulls a specific number of messages from a chat.
        * @param chatId The ID of the chat.
        * @param n The number of messages to fetch.
        */
    void pull_num_chat_messages(int chatId, int n);

    /**
         * @brief Sets the read status of a chat for a specific user.
         * @param chatId The ID of the chat.
         * @param userId The ID of the user.
         */
    void set_read(int chatId, int userId);

    /**
         * @brief Sets the unread status of a chat for all users.
         * @param chatId The ID of the chat.
         */
    void set_unread(int chatId);

    /**
        * @brief Retrieves the maximum chat ID from the database.
        */
    void max_chatId();

    /**
         * @brief Retrieves the maximum message ID from the database.
         */
    void max_messageId();

};
} // namespace db
#endif // CHATDB_H
