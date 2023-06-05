#ifndef DB_PROFILEDB_H
#define DB_PROFILEDB_H

#include "database.h"
#include <string>

namespace db {

/**
 * @brief The ProfileDB class provides functionality to interact with the profile-related tables in the database.
 */
class ProfileDB : public Database {
public:
    /**
     * @brief Constructs a ProfileDB object with the specified database file.
     * @param file The database file name.
     */
    ProfileDB(std::string file);

    /**
         * @brief Fetches the profile ID for a given user ID.
         * @param user_id The user ID.
         */
    void fetch_profile_id(int user_id);

    /**
         * @brief Fetches the display name of a profile based on the provided display name.
         * @param display_name The display name.
         */
    void fetch_profile_display_name(std::string display_name);

    /**
        * @brief Fetches the links associated with a user ID.
        * @param user_id The user ID.
        */
    void fetch_links(int user_id);

    /**
         * @brief Fetches all pals that belong to a user.
         * @param user_id The user ID.
         */
    void fetch_pals(int user_id);

    /**
        * @brief Fetches a pal by ID.
        * @param id The pal ID.
        */
    void fetch_pal(int id);

    /**
         * @brief Fetches the shoal tag for a member ID.
         * @param member_id The member ID.
         */
    void fetch_shoal_tag(int member_id);

    /**
         * @brief Fetches the reef information for a given from_user_id.
         * @param from_user_id The from_user_id.
         */
    void fetch_reef(int from_user_id);

    /**
        * @brief Edits the profile information for a given ID.
        * @param id The profile ID.
        * @param avatar_id The avatar ID.
        * @param display_name The display name.
        * @param bio The biography.
        * @param fish_day The fish day.
        * @param theme The theme.
        */
    void edit_profile(int id, int avatar_id, std::string display_name,
                      std::string bio, std::string fish_day, int theme);

    /**
         * @brief Edits the display name for a given user ID.
         * @param user_id The user ID.
         * @param display_name The new display name.
         */
    void edit_display_name(int user_id, std::string display_name);

    /**
         * @brief Edits the avatar ID for a given user ID.
         * @param user_id The user ID.
         * @param avatar_id The new avatar ID.
         */
    void edit_avatarId(int user_id, int avatar_id);

    /**
         * @brief Edits the biography for a given user ID.
         * @param user_id The user ID.
         * @param bio The new biography.
         */
    void edit_bio(int user_id, std::string bio);

    /**
         * @brief Edits the fish day for a given user ID.
         * @param user_id The user ID.
         * @param fish_day The new fish day.
         */
    void edit_fishDay(int user_id, std::string fish_day);

    /**
         * @brief Edits the theme for a given user ID.
         * @param user_id The user ID.
         * @param theme The new theme.
         */
    void edit_theme(int user_id, int theme);

    /**
         * @brief Inserts a shoal membership for a member ID and shoal tag.
         * * @param member_id The member ID.
     * @param shoal_tag The shoal tag.
     */
    void insert_shoal_membership(int member_id, std::string shoal_tag);

    /**
         * @brief Removes a shoal membership for a member ID and shoal tag.
         * @param member_id The member ID.
         * @param shoal_tag The shoal tag.
         */
    void remove_shoal_membership(int member_id, std::string shoal_tag);

    /**
         * @brief Inserts a link for a given user ID, label, and link.
         * @param user_id The user ID.
         * @param label The link label.
         * @param link The link URL.
         */
    void insert_link(int user_id, std::string label, std::string link);

    /**
         * @brief Removes a link for a given user ID, tag, and link.
         * @param user_id The user ID.
         * @param tag The link tag.
         * @param link The link URL.
         */
    void remove_link(int user_id, std::string tag, std::string link);

    /**
         * @brief Creates a reef between two user IDs.
         * @param from_user_id The from_user_id.
         * @param to_user_id The to_user_id.
         */
    void create_reef(int from_user_id, int to_user_id);

    /**
         * @brief Removes a reef between two user IDs.
         * @param from_user_id The from_user_id.
         * @param to_user_id The to_user_id.
         */
    void remove_reef(int from_user_id, int to_user_id);

    /**
         * @brief Adds a pal for a given user ID, pal ID, avatar ID, name, species, birthday, and bio.
         * @param user_id The user ID.
         * @param id The pal ID.
         * @param avatar_id The avatar ID.
         * @param name The pal's name.
         * @param species The pal's species.
         * @param birthday The pal's birthday.
         * @param bio The pal's biography.
         */
    void add_pal(int user_id, int id, int avatar_id, std::string name,
                 std::string species, std::string birthday, std::string bio);

    /**
         * @brief Removes a pal for a given ID.
         * @param id The pal ID.
         */
    void remove_pal(int id);

    /**
         * @brief Edits the avatar ID for a given pal ID.
         * @param id The pal ID.
         * @param avatar_id The new avatar ID.
         */
    void edit_pal_avatar_id(int id, int avatar_id);

    /**
         * @brief Edits the name for a given pal ID.
         * @param id The pal ID.
         * @param name The new name.
         */
    void edit_pal_name(int id, std::string name);

    /**
         * @brief Edits the species for a given pal ID.
         * @param id The pal ID.
         * @param species The new species.
         */
    void edit_pal_species(int id, std::string species);

    /**
         * @brief Edits the birthday for a given pal ID.
         * @param id The pal ID.
         * @param birthday The new birthday.
         */
    void edit_pal_birthday(int id, std::string birthday);

    /**
         * @brief Edits the biography for a given pal ID.
         * @param id The pal ID.
         * @param bio The new biography.
         */
    void edit_pal_bio(int id, std::string bio);

    /**
         * @brief Inserts a profile avatar for a given ID and content.
         * @param id The ID.
         * @param content The avatar content.
         */
    void insert_profile_avatar(int id, QByteArray content);

    /**
         * @brief Fetches the profile avatar for a given ID.
         * @param id The ID.
         */
    void fetch_profile_avatar(int id);

    /**
         * @brief Finds the maximum pal ID.
         */
    void max_pal_id();

    /**
         * @brief Retrieves the fish time for a given ID.
         * @param id The ID.
         */
    void fish_time(int id);

    /**
         * @brief Creates a profile with the specified ID and fish day.
         * @param id The profile ID.
         * @param fishday The fish day.
         */
    void create_profile(int id, std::string fishday);
};

} // namespace db

#endif // DB_PROFILEDB_H
