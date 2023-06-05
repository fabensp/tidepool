#ifndef PAL_H
#define PAL_H

#include <string>

using namespace std;

namespace profile {

class Pal
{
public:

    /**
     * @brief Pal default constructor
     */
    Pal();

    //Setters
    void set_id(int _id) { id = _id; }
    void set_avatarId(int _avatarId) { avatarId = _avatarId; }
    void set_name(string _name) { name = _name; }
    void set_species(string _species) { species = _species; }
    void set_birthday(string _birthday) { birthday = _birthday; }
    void set_bio(string _bio) { bio = _bio; }

    //Getters
    int get_id() { return id; }
    int get_avatarId() { return avatarId; }
    string get_name() { return name; }
    string get_species() { return species; }
    string get_bio() { return bio; }
    string get_birthday() { return birthday; }

private:
    int id;
    int avatarId;
    string name;
    string species;
    string birthday;
    string bio;
};

}

#endif // PAL_H
