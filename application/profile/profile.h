#ifndef PROFILE_H
#define PROFILE_H

#include <string.h>
#include <vector>
#include "../user/account.h"
#include "pal.h"

using namespace std;

namespace profile {

class Profile
{
    friend class ProfileIO;

public:

    /**
     * @brief Profile default constructor
     */
    Profile();

    /**
     * @brief ~Profile default destructor
    */
    ~Profile();

    /**
     * @brief addShoalMembership adds a shoal membership to the shoal vector
     * @param shoal_membership The new shoal membership of the profile
     */
    void addShoalMembership(string shoal_membership) { shoal_tag.push_back(shoal_membership); }

    /**
     * @brief removeShoalMembership removes a given shoal from the shoal vector
     * @param shoal_membership The name of the shoal membership
     */
    void removeShoalMembership(string shoal_membership);

    /**
     * @brief removePal removes a pal from the pal vector
     * @param p Pal to remove
     */
    void removePal(Pal* p);

    /**
     * @brief addToReef add an account to the reef vector
     * @param u Account to add
     */
    void addToReef(user::Account& u) { reef_list.push_back(u); }

    /**
     * @brief removeFromReef removes a user from the reef vector
     * @param to user account to remove
     */
    void removeFromReef(user::Account& to);

    //Setters
    void set_display_name(string d) { display_name = d; }
    void set_bio(string b) { bio = b; }
    void add_pal(Pal* p) { pals.push_back(p); }

    //Getters
    int get_id() { return id; }
    user::Account* get_account() { return account; }
    string get_display_name() { return display_name; }
    string get_bio() { return bio; }
    int get_theme() { return theme; }
    int get_avatar_id(){ return avatarId; }
    string get_fish_date(){ return fish_date; }
    vector<string> get_link_labels() { return link_labels; }
    vector<string> get_link_addresses() { return link_addresses; }
    Pal* get_pal(int i) {
        if (i > (int)pals.size() - 1) return nullptr;
        return pals[i];
    }
    vector<Pal*> get_pals() { return pals; }
    vector<user::Account> get_reef() { return reef_list; }
    vector<string> get_shoal_membership() { return shoal_tag; }

private:
    int id;
    user::Account* account;
    string display_name;
    int avatarId;
    string fish_date;
    int theme;
    string bio;
    vector<string> link_labels;
    vector<string> link_addresses;
    vector<Pal*> pals;
    vector<string> shoal_tag;
    vector<user::Account> reef_list;
};

}

#endif // PROFILE_H
