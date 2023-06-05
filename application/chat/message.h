#ifndef MESSAGE_H
#define MESSAGE_H
#include "../user/account.h"
#include <string>

using namespace std;

namespace chat {

class Message
{

    friend class ChatIO;

public:
    Message();

    /*
     * Constructor that takes a sender
     * @param s       Sender of the message
     * @param m       The message content
    */
    Message(user::Account s, string m);

    //Setter for the message class
    void set_sender(user::Account s) { sender = s; }

    //Getters for the message class
    int get_id () { return id; }
    user::Account get_sender() { return sender; }
    string get_content() { return message; }
    string get_timestamp() { return timestamp; }

private:
    int id;
    user::Account sender;
    string message;
    string timestamp;
};

}

#endif // MESSAGE_H
