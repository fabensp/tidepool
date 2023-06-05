#include "chat.h"

chat::Chat::Chat() {

}
/*
 * Default Destructor
*/
chat::Chat::~Chat() {
    for (Message* m : messages) delete m;
}

/*
 *  Add a message to the message vector
 *  @param m Message to add
*/
void chat::Chat::add_message(chat::Message* m) {
    messages.push_back(m);
}

