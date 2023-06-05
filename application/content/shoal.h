
#ifndef CONTENT_SHOAL_H
#define CONTENT_SHOAL_H

#include <string>
namespace content {

class Shoal
{

    friend class PostIO;

public:

    /**
     * @brief Shoal default constructor
     */
    Shoal();

    /**
     * @brief Shoal constructor with the given information
     * @param tag         Name of the shoal
     * @param description Description of the shoal
     * @param theme       Theme of the shoal
     * @param creator_id  User who created the shoal
     */
    Shoal(std::string tag, std::string description, int theme, int creator_id) :
        tag(tag), description(description), theme(theme),
        creator_id(creator_id) {}

    void set_tag(std::string t) { tag = t; }
    void set_desc(std::string d) { description = d; }
    void set_theme(int t) { theme = t; }
    void set_creator_id(int id) { creator_id = id; }

    std::string get_tag() { return tag; }
    std::string get_description() { return description; }
    int get_theme() { return theme; }
    int get_creator_id() { return creator_id; }

private:
    std::string tag;
    std::string description;
    int theme;
    int creator_id;
};

} // namespace content

#endif // CONTENT_SHOAL_H
