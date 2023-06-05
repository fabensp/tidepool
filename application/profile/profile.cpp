#include "profile.h"

/**
 * @brief Profile default constructor
 */
profile::Profile::Profile():
    id(-1),
    account(new user::Account()),
    display_name("empty"),
    bio("empty"),
    link_labels(),
    link_addresses(),
    pals()
{

}

/**
 * @brief ~Profile default destructor
*/
profile::Profile::~Profile() {
    delete account;
}

/**
 * @brief removeShoalMembership removes a given shoal from the shoal vector
 * @param shoal_membership The name of the shoal membership
 */
void profile::Profile::removeShoalMembership(string shoal_membership) {
    for (int i = 0; i < shoal_tag.size(); i++) {
        string temp = shoal_tag[i];
        if (temp.compare(shoal_membership) == 0) {
            shoal_tag.erase(shoal_tag.begin() + i);
        }
    }
}

/**
 * @brief removePal removes a pal from the pal vector
 * @param p Pal to remove
 */
void profile::Profile::removePal(Pal* p) {
    for (int i = 0; i < pals.size(); i++) {
        if (p->get_id() == pals[i]->get_id()) {
            pals.erase(pals.begin() + i);
        }
    }
}

/**
 * @brief removeFromReef removes a user from the reef vector
 * @param to user account to remove
 */
void profile::Profile::removeFromReef(user::Account& to) {
    for (int i = 0; i < reef_list.size(); i++) {
        if (reef_list[i].get_id() == to.get_id()) {
            reef_list.erase(reef_list.begin() + i);
        }
    }
}
