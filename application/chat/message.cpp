#include "message.h"
chat::Message::Message(){

}
/*
 * Constructor that takes a sender
 * @param s       Sender of the message
 * @param m       The message content
*/
chat::Message::Message(user::Account s, string m) : sender(s), message(m) {}


