#ifndef DATACHAT_H
#define DATACHAT_H
#include <string>
#include <vector>
#include "message.h"
#include "../user/account.h"

using namespace std;

namespace chat {

class Chat
{

    friend class ChatIO;

public:
    Chat();

    /*
     * Default Destructor
    */
    ~Chat();

    //Setters for the chat class
    void set_read() { unread = 0; }
    void set_unread() { unread = 1; }
    void set_theme(int theme) { this->theme = theme; }
    void set_title(string title) { this->title = title; }

    //Getters for the chat class
    int get_theme() { return theme; }
    int get_unread() { return unread; }
    int get_id() { return id; }
    string get_title() { return title; }
    vector<Message*> get_messages() { return messages; }

    /*
     *  Add a message to the message vector
     *  @param m Message to add
    */
    void add_message(chat::Message* m);


private:
    int id;
    int unread;
    int theme;
    string title;
    vector<chat::Message*> messages;
};

}

#endif // DATACHAT_H
