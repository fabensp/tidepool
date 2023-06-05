#ifndef PROFILEIO_H
#define PROFILEIO_H
#include "../database/profiledb.h"
#include "../user/accountio.h"
#include "pal.h"
#include "profile.h"
#include <string>
#include <vector>
#include <QFile>

using namespace std;

namespace profile {

class ProfileIO {
    friend class ProfileIOTest;

public:
    /**
     * @brief ProfileIO defualt constructor
     */
    ProfileIO();

    /**
     * @brief ProfileIO constructor that links to the profile database
     * @param _db Profile database
     */
    ProfileIO(db::ProfileDB* _db);

    /**
     * @brief create_profile sends a new profie to the database class
     * @param id Id of the new profile
     * @param fishday Day the new profile started liking fish
     * @return 1 if successful, 0 if not
     */
    int create_profile(int id, std::string fishday);

    /**
     * @brief pull_profile_id Pulls a profile from the database given the id
     * @param p Profile to push the info into
     * @param id Identifier of the profile to be pulled
     * @return 1 if successful, 0 if not
     */
    int pull_profile_id(Profile& p, int id);

    /**
     * @brief pull_profile_display_name Pulls a profile from the database given the display name
     * @param p            Profile to push the info into
     * @param display_name Display name of the profile to pull
     * @return 1 if successful, 0 if not
     */
    int pull_profile_display_name(Profile& p, string display_name);

    /**
     * @brief pull_links pulls the links in a profile
     * @param p Profile to pull links from
     * @return 1 if successful, 0 if not
     */
    int pull_links(Profile &p);

    /**
     * @brief pull_pals pulls the pals in a profile from the database
     * @param p Profile to push pals into
     * @return 1 if successful, 0 if not
     */
    int pull_pals(Profile &p);

    /**
     * @brief pull_shoal_tag gets the shoals in a profile from the database
     * @param p Profie to push shoals into
     * @return 1 if successful, 0 if not
     */
    int pull_shoal_tag(Profile &p);

    /**
     * @brief pull_reef gets the reef list in a profile from the database
     * @param p Profile to push reef into
     * @return 1 if successul, 0 if not
     */
    int pull_reef(Profile &p);

    /**
     * @brief edit_profile sends all the passed profile's info to the db
     * @param p Profile with new info
     * @return 1 if successful, 0 if not
     */
    int edit_profile(Profile& p);

    /**
     * @brief edit_display_name change the display name of a profile
     * @param p            Profile to change display name of
     * @param display_name New display name
     * @return 1 if successful, 0 if not
     */
    int edit_display_name(Profile& p, string display_name);

    /**
     * @brief edit_avatar_image change the avatar of a profile
     * @param p     Profile to change avatar of
     * @param image Integer value of new image
     * @return 1 if successful, 0 if not
     */
    int edit_avatar_image(Profile& p, int image);

    /**
     * @brief edit_bio change the bio of a profile
     * @param p   Profile to change bio of
     * @param bio New biography of profile
     * @return 1 if successful, 0 if not
     */
    int edit_bio(Profile& p, string bio);

    /**
     * @brief edit_fish_date change the fish date of a profile
     * @param p         Profile to change fish date of
     * @param fish_date New fish date of profile
     * @return 1 if successful, 0 if not
     */
    int edit_fish_date(Profile& p, string fish_date);

    /**
     * @brief edit_theme change to theme of a profile
     * @param p     Profile to change theme of
     * @param theme New theme of profile
     * @return 1 if successful, 0 if not
     */
    int edit_theme(Profile& p, int theme);

    /**
     * @brief add_shoal_membership adds a new shoal to the profile
     * @param p                Profile to add shoal into
     * @param shoal_membership name of the new shoal
     * @return 1 if successful, 0 if not
     */
    int add_shoal_membership(Profile& p, string shoal_membership);

    /**
     * @brief remove_shoal_membership removes a shoal from the profile
     * @param p                Profile to remove shoal from
     * @param shoal_membership Name of the shoal to remove
     * @return 1 if successful, 0 if not
     */
    int remove_shoal_membership(Profile& p, string shoal_membership);

    /**
     * @brief add_link adds a new link to the profile
     * @param p    Profile to add link to
     * @param tag  Name of the new link
     * @param link New link
     * @return 1 if successful, 0 if not
     */
    int add_link(Profile& p, string tag, string link);

    /**
     * @brief remove_link removes a link from the profile
     * @param p    Profile to remove link from
     * @param tag  Name of the link to remove
     * @param link Link to remove
     * @return 1 if successful, 0 if not
     */
    int remove_link(Profile& p, string tag, string link);

    /**
     * @brief add_user_to_reef Adds a user to to reef vector
     * @param p    Profile to add user into
     * @param from Account to add new reef into
     * @param to   Account being added into the reef
     * @return 1 if successful, 0 if not
     */
    int add_user_to_reef(profile::Profile& p, user::Account& from, user::Account& to);

    /**
     * @brief remove_reef removes a user from the reef vector
     * @param p    Profile to remove reef from
     * @param from The current user
     * @param to   The other user
     * @return 1 if successful, 0 if not
     */
    int remove_reef(profile::Profile& p, user::Account& from, user::Account& to);

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
    int create_pal(Profile& p, int avatarId, string name, string species,
                   string bday, string bio);

    /**
     * @brief remove_pal removes a pal from the profile
     * @param p   Profile to remove pal from
     * @param pal Pal to remove
     * @return 1 if successful, 0 if not
     */
    int remove_pal(Profile& p, Pal* pal);

    /**
     * @brief edit_pal_avatar_id Edits the pals avatar id
     * @param p         Pal to edit
     * @param avatar_id New avatar identifier
     * @return 1 if successful, 0 if not
     */
    int edit_pal_avatar_id(Pal* p, int avatar_id);

    /**
     * @brief edit_pal_name Edits the pals name
     * @param p    Pal to edit
     * @param name New pal name
     * @return 1 if successful, 0 if not
     */
    int edit_pal_name(Pal* p, string name);

    /**
     * @brief edit_pal_species Edits the pals species
     * @param p       Pal to edit
     * @param species New pal species
     * @return 1 if successful, 0 if not
     */
    int edit_pal_species(Pal* p, string species);

    /**
     * @brief edit_pal_birthday edits the pals birthday
     * @param p       Pal to edit
     * @param bday    New pal birthday
     * @return 1 if successful, 0 if not
     */
    int edit_pal_birthday(Pal* p, string bday);

    /**
     * @brief edit_pal_bio edits the pal biography
     * @param p Pal to edit
     * @param bio New pal biography
     * @return 1 if successful, 0 if not
     */
    int edit_pal_bio(Pal* p, string bio);

    /**
     * @brief set_profile_avatar sets the profile avatar for different files
     * @param avatarId  New avatar id
     * @param file_name File name with image
     * @return 1 if successful, 0 if not
     */
    int set_profile_avatar(int avatarId, string file);

    /**
     * @brief fish_time Formatting for the display of the fish enthusiast
     * @param p Profile to get fish date from
     * @return The string format of the display
     */
    std::string fish_time(Profile* p);

    /**
     * @brief get_profile_avatar Gets the avatar of a profile
     * @param pix      Storage of the image
     * @param avatarId Avatar identifier
     * @return 1 if successful, 0 if not
     */
    int get_profile_avatar(QByteArray* pix, int avatarId);

private:
    db::ProfileDB* db;
    user::AccountIO aio;

    /**
     * @brief next_pal_id gets the next id for a pal in the database
     * @return the new pal id
     */
    int next_pal_id();
};
} // namespace profile

#endif // PROFILEIO_H
