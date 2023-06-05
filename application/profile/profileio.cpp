#include "profileio.h"

/**
 * @brief ProfileIO defualt constructor
 */
profile::ProfileIO::ProfileIO()
{

}

/**
 * @brief ProfileIO constructor that links to the profile database
 * @param _db Profile database
 */
profile::ProfileIO::ProfileIO(db::ProfileDB* db) : db(db), aio((db::UserDB*)db) {}

/**
 * @brief create_profile sends a new profie to the database class
 * @param id Id of the new profile
 * @param fishday Day the new profile started liking fish
 * @return 1 if successful, 0 if not
 */
int profile::ProfileIO::create_profile(int id, std::string fishday) {
    if (id < 0) return 0;
    db->create_profile(id, fishday);
    return 1;
}

/**
 * @brief pull_profile_id Pulls a profile from the database given the id
 * @param p Profile to push the info into
 * @param id Identifier of the profile to be pulled
 * @return 1 if successful, 0 if not
 */
int profile::ProfileIO::pull_profile_id(profile::Profile& p, int id) {
    if (id < 0) return 0;
    db->fetch_profile_id(id);

    if (db->next()) {
        p.id = id;
        p.avatarId = db->result()->value("avatar_id").toInt();
        p.display_name = db->result()->value("display_name").toString().toStdString();
        p.bio = db->result()->value("bio").toString().toStdString();
        p.fish_date = db->result()->value("fish_day").toString().toStdString();
        p.theme = db->result()->value("theme").toInt();

        //Get the stuff stored in other tables
        pull_links(p);
        pull_pals(p);
        pull_shoal_tag(p);
        pull_reef(p);
    } else return 0;

    aio.pull(*p.account, id);

    return 1;
}

/**
 * @brief pull_profile_display_name Pulls a profile from the database given the display name
 * @param p            Profile to push the info into
 * @param display_name Display name of the profile to pull
 * @return 1 if successful, 0 if not
 */
int profile::ProfileIO::pull_profile_display_name(profile::Profile& p,
                                          string display_name) {
    db->fetch_profile_display_name(display_name);

    //Get the stuff stored in the profile table
    if (db->next()) {
        p.id = db->result()->value("user_id").toInt();
        p.avatarId = db->result()->value("avatar_id").toInt();
        p.display_name = display_name;
        p.bio = db->result()->value("bio").toString().toStdString();
        p.fish_date = db->result()->value("fish_day").toString().toStdString();
        p.theme = db->result()->value("theme").toInt();

        //Get the stuff stored in other tables
        pull_links(p);
        pull_pals(p);
        pull_shoal_tag(p);
        pull_reef(p);
    } else return 0;

    return 1;
}

/**
 * @brief pull_links pulls the links in a profile
 * @param p Profile to pull links from
 * @return 1 if successful, 0 if not
 */
int profile::ProfileIO::pull_links(Profile &p) {
    vector<string> labels;
    vector<string> addresses;
    if (p.id < 0) return 0;
    db->fetch_links(p.id);

    int n = 0;
    while (db->next()) {
        string label;
        string address;
        label = db->result()->value(0).toString().toStdString();
        address = db->result()->value(1).toString().toStdString();
        labels.push_back(label);
        addresses.push_back(address);
    }
    p.link_labels = labels;
    p.link_addresses = addresses;
    return 1;
}

/**
 * @brief pull_pals pulls the pals in a profile from the database
 * @param p Profile to push pals into
 * @return 1 if successful, 0 if not
 */
int profile::ProfileIO::pull_pals(Profile &p) {
    vector<Pal*> pals;
    if (p.id < 0) return 0;
    db->fetch_pals(p.id);

    while (db->next()) {
        Pal* pal = new Pal();
        pal->set_id(db->result()->value(0).toInt());
        pal->set_avatarId(db->result()->value(1).toInt());
        pal->set_name(db->result()->value(2).toString().toStdString());
        pal->set_species(db->result()->value(3).toString().toStdString());
        pal->set_birthday(db->result()->value(4).toString().toStdString());
        pal->set_bio(db->result()->value(5).toString().toStdString());
        pals.push_back(pal);
    }
    p.pals = pals;
    return 1;
}

/**
 * @brief pull_shoal_tag gets the shoals in a profile from the database
 * @param p Profie to push shoals into
 * @return 1 if successful, 0 if not
 */
int profile::ProfileIO::pull_shoal_tag(Profile &p) {
    vector<string> tags;
    if (p.id < 0) return 1;
    db->fetch_shoal_tag(p.id);

    while (db->next()) {
        string tag;
        tag = db->result()->value("shoal_tag").toString().toStdString();
        tags.push_back(tag);
    }
    p.shoal_tag = tags;
    return 1;
}

/**
 * @brief pull_reef gets the reef list in a profile from the database
 * @param p Profile to push reef into
 * @return 1 if successul, 0 if not
 */
int profile::ProfileIO::pull_reef(Profile &p) {
    vector<user::Account> reef;
    if (p.id < 0) return 0;
    db->fetch_reef(p.id); //Should get the to_user_ids

    vector<int> ids;
    while (db->next()) {
        ids.push_back(db->result()->value("to_user_id").toInt());
    }

    for (int i = 0; i < (int)ids.size(); i++) {
        user::Account a;
        aio.pull(a, ids[i]);
        reef.push_back(a);
    }
    p.reef_list = reef;
    return 1;
}

/**
 * @brief edit_profile sends all the passed profile's info to the db
 * @param p Profile with new info
 * @return 1 if successful, 0 if not
 */
int profile::ProfileIO::edit_profile(profile::Profile& p) {
    if (p.id < 0) return 0;
    db->fetch_profile_id(p.id);

    if (db->next()) {
        db->edit_profile(p.id, p.avatarId, p.display_name, p.bio, p.fish_date,
                         p.theme);
    } else return 0;

    return 1;
}

/**
 * @brief edit_display_name change the display name of a profile
 * @param p            Profile to change display name of
 * @param display_name New display name
 * @return 1 if successful, 0 if not
 */
int profile::ProfileIO::edit_display_name(profile::Profile& p,
                                          string display_name) {
    if (p.id < 0) return 0;
    db->fetch_profile_id(p.id);

    if (db->next()) {
        p.display_name = display_name;
        db->edit_display_name(p.id, display_name);
    } else return 0;

    return 1;
}

/**
 * @brief edit_avatar_image change the avatar of a profile
 * @param p     Profile to change avatar of
 * @param image Integer value of new image
 * @return 1 if successful, 0 if not
 */
int profile::ProfileIO::edit_avatar_image(profile::Profile& p, int image) {
    if (p.id < 0) return 0;
    db->fetch_profile_id(p.id);

    if (db->next()) {
        p.avatarId = image;
        db->edit_avatarId(p.id, image);
    } else return 0;

    return 1;
}

/**
 * @brief edit_bio change the bio of a profile
 * @param p   Profile to change bio of
 * @param bio New biography of profile
 * @return 1 if successful, 0 if not
 */
int profile::ProfileIO::edit_bio(profile::Profile& p, string bio) {
    if (p.id < 0) return 0;
    db->fetch_profile_id(p.id);

    if (db->next()) {
        p.bio = bio;
        db->edit_bio(p.id, bio);
    } else return 0;

    return 1;
}

/**
 * @brief edit_fish_date change the fish date of a profile
 * @param p         Profile to change fish date of
 * @param fish_date New fish date of profile
 * @return 1 if successful, 0 if not
 */
int profile::ProfileIO::edit_fish_date(profile::Profile& p, string fish_date) {
    if (p.id < 0) return 0;
    db->fetch_profile_id(p.id);

    if (db->next()) {
        p.fish_date = fish_date;
        db->edit_fishDay(p.id, fish_date);
    } else return 0;

    return 1;
}

/**
 * @brief edit_theme change to theme of a profile
 * @param p     Profile to change theme of
 * @param theme New theme of profile
 * @return 1 if successful, 0 if not
 */
int profile::ProfileIO::edit_theme(profile::Profile& p, int theme) {
    if (p.id < 0) return 0;
    db->fetch_profile_id(p.id);

    if (db->next()) {
        p.theme = theme;
        db->edit_theme(p.id, theme);
    } else return 0;

    return 1;
}

/**
 * @brief add_shoal_membership adds a new shoal to the profile
 * @param p                Profile to add shoal into
 * @param shoal_membership Name of the new shoal
 * @return 1 if successful, 0 if not
 */
int profile::ProfileIO::add_shoal_membership(profile::Profile& p,
                                              string shoal_membership) {
    if (p.id < 0) return 0;
    p.addShoalMembership(shoal_membership);
    db->insert_shoal_membership(p.id, shoal_membership);
    return 1;
}

/**
 * @brief remove_shoal_membership removes a shoal from the profile
 * @param p                Profile to remove shoal from
 * @param shoal_membership Name of the shoal to remove
 * @return 1 if successful, 0 if not
 */
int profile::ProfileIO::remove_shoal_membership(profile::Profile& p, string shoal_membership) {
    if (p.id < 0) return 0;
    p.removeShoalMembership(shoal_membership);
    db->remove_shoal_membership(p.id, shoal_membership);
    return 1;
}

/**
 * @brief add_link adds a new link to the profile
 * @param p    Profile to add link to
 * @param tag  Name of the new link
 * @param link New link
 * @return 1 if successful, 0 if not
 */
int profile::ProfileIO::add_link(profile::Profile& p, string tag, string link) {
    if (p.id < 0) return 0;
    db->insert_link(p.id, tag, link);
    p.link_labels.push_back(tag);
    p.link_addresses.push_back(link);
    return 0;
}

/**
 * @brief remove_link removes a link from the profile
 * @param p    Profile to remove link from
 * @param tag  Name of the link to remove
 * @param link Link to remove
 * @return 1 if successful, 0 if not
 */
int profile::ProfileIO::remove_link(profile::Profile& p, string tag,
                                    string link) {
    if (p.id < 0) return 0;
    db->remove_link(p.id, tag, link);
    pull_links(p);
    return 0;
}

/**
 * @brief add_user_to_reef adds a user to to reef vector
 * @param p    Profile to add user into
 * @param from Account to add new reef into
 * @param to   Account being added into the reef
 * @return 1 if successful, 0 if not
 */
int profile::ProfileIO::add_user_to_reef(profile::Profile& p,
                                         user::Account& from,
                                         user::Account& to) {
    if (from.get_id() == -1 || to.get_id() == -1) return 0;
    db->create_reef(from.get_id(), to.get_id());
    p.addToReef(to);
    return 1;
}

/**
 * @brief remove_reef removes a user from the reef vector
 * @param p    Profile to remove reef from
 * @param from The current user
 * @param to   The other user
 * @return 1 if successful, 0 if not
 */
int profile::ProfileIO::remove_reef(profile::Profile& p, user::Account& from, user::Account& to) {
    if (from.get_id() == -1 || to.get_id() == -1) return 0;
    db->remove_reef(from.get_id(), to.get_id());
    p.removeFromReef(to);
    return 1;
}

/**
 * @brief create_pal creates a pal with given information
 * @param p        Profile to create new pal into
 * @param avatarId Avatar identifer of new pal
 * @param name     Name of new pal
 * @param species  Species of new pal
 * @param bday     Birthday of new pal
 * @param bio      Biography of new pal
 * @return 1 if successful, 0 if not
 */
int profile::ProfileIO::create_pal(profile::Profile& p, int avatarId,
                                   string name, string species, string bday,
                                   string bio) {
    if (p.id < 0) return 0;
    profile::Pal* pal = new Pal();
    int id = next_pal_id();
    pal->set_id(id);
    pal->set_avatarId(avatarId);
    pal->set_name(name);
    pal->set_species(species);
    pal->set_birthday(bday);
    pal->set_bio(bio);
    p.add_pal(pal);

    db->add_pal(p.get_id(), id, avatarId, name, species, bday, bio);
    return 1;
}

/**
 * @brief remove_pal removes a pal from the profile
 * @param p   Profile to remove pal from
 * @param pal Pal to remove
 * @return 1 if successful, 0 if not
 */
int profile::ProfileIO::remove_pal(Profile& p, Pal* pal) {
    if (p.id < 0 || pal->get_id() < 0) return 0;
    p.removePal(pal);
    db->remove_pal(pal->get_id());
    return 1;
}

/**
 * @brief edit_pal_avatar_id Edits the pals avatar id
 * @param p         Pal to edit
 * @param avatar_id New avatar identifier
 * @return 1 if successful, 0 if not
 */
int profile::ProfileIO::edit_pal_avatar_id(profile::Pal* p, int avatar_id) {
    if (p->get_id() < 0) return 0;
    db->fetch_pal(p->get_id());

    if (db->next()) {
        p->set_avatarId(avatar_id);
        db->edit_pal_avatar_id(p->get_id(), avatar_id);
    } else return 0;

    return 1;
}

/**
 * @brief edit_pal_name Edits the pals name
 * @param p    Pal to edit
 * @param name New pal name
 * @return 1 if successful, 0 if not
 */
int profile::ProfileIO::edit_pal_name(profile::Pal* p, string name) {
    if (p->get_id() < 0) return 0;
    db->fetch_pal(p->get_id());

    if (db->next()) {
        p->set_name(name);
        db->edit_pal_name(p->get_id(), name);
    } else return 0;

    return 1;
}

/**
 * @brief edit_pal_species Edits the pals species
 * @param p       Pal to edit
 * @param species New pal species
 * @return 1 if successful, 0 if not
 */
int profile::ProfileIO::edit_pal_species(profile::Pal* p, string species) {
    if (p->get_id() < 0) return 0;
    db->fetch_pal(p->get_id());

    if (db->next()) {
        p->set_species(species);
        db->edit_pal_species(p->get_id(), species);
    } else return 0;

    return 1;
}

/**
 * @brief edit_pal_birthday edits the pals birthday
 * @param p       Pal to edit
 * @param bday    New pal birthday
 * @return 1 if successful, 0 if not
 */
int profile::ProfileIO::edit_pal_birthday(profile::Pal* p, string bday) {
    if (p->get_id() < 0) return 0;
    db->fetch_pal(p->get_id());

    if (db->next()) {
        p->set_birthday(bday);
        db->edit_pal_birthday(p->get_id(), bday);
    } else return 0;

    return 1;
}

/**
 * @brief edit_pal_bio edits the pal biography
 * @param p Pal to edit
 * @param bio New pal biography
 * @return 1 if successful, 0 if not
 */
int profile::ProfileIO::edit_pal_bio(profile::Pal* p, string bio) {
    if (p->get_id() < 0) return 0;
    db->fetch_pal(p->get_id());

    if (db->next()) {
        p->set_bio(bio);
        db->edit_pal_bio(p->get_id(), bio);
    } else return 0;

    return 1;
}

/**
 * @brief set_profile_avatar sets the profile avatar for different files
 * @param avatarId  New avatar id
 * @param file_name File name with image
 * @return 1 if successful, 0 if not
 */
int profile::ProfileIO::set_profile_avatar(int avatarId, string file_name) {
    QFile file(QString::fromStdString(file_name));
    if (file.exists()) return 0;
    file.open(QIODevice::ReadOnly);
    QByteArray bytes = file.readAll();
    db->insert_profile_avatar(avatarId, bytes);
    return 1;
}

/**
 * @brief fish_time Formatting for the display of the fish enthusiast
 * @param p Profile to get fish date from
 * @return The string format of the display
 */
std::string profile::ProfileIO::fish_time(Profile* p) {
    if (p->account->get_id() < 0) return "";
    db->fish_time(p->get_id());
    int d;
    if (db->next()) d = db->result()->value(0).toInt();
    else return "";
    if (!d) return "";
    int y = d / 365;
    d %= 365;
    int m = d / 30;
    d %= 30;
    std::string out = " has been a Fish Enthusiast for ";
    out += (y) ? std::to_string(y) + " years " : "";
    out += (m) ? std::to_string(m) + " months " : "";
    out += (d) ? std::to_string(d) + " days " : "";
    return out;
}

/**
 * @brief get_profile_avatar Gets the avatar of a profile
 * @param pix      Storage of the image
 * @param avatarId Avatar identifier
 * @return 1 if successful, 0 if not
 */
int profile::ProfileIO::get_profile_avatar(QByteArray* pix, int avatarId) {
    if (avatarId < 0) return 0;
    db->fetch_profile_avatar(avatarId);
    *pix = db->result()->value(0).toByteArray();
    return 1;
}

/**
 * @brief next_pal_id gets the next id for a pal in the database
 * @return the new pal id
 */
int profile::ProfileIO::next_pal_id() {
    db->max_pal_id();

    int num;
    if (db->next()) {
        num = db->result()->value("Max(id)").toInt();
    } else return -100;
    int id = num + 1;
    return id;

}

