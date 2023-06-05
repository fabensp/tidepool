#ifndef POST_H
#define POST_H

#include "../user/account.h"
#include "shoal.h"
#include <string>
using namespace std;

namespace content {

class Survey {
public:


    void set_id(int _id) { id = _id; }
    void set_opt1msg(string _opt1msg) { opt1msg = _opt1msg; }
    void set_opt2msg(string _opt2msg) { opt1msg = _opt2msg; }
    void set_opt3msg(string _opt3msg) { opt1msg = _opt3msg; }
    void set_opt4msg(string _opt4msg) { opt1msg = _opt4msg; }
    void set_opt1votes(int _opt1votes) { opt1votes = _opt1votes; }
    void set_opt2votes(int _opt2votes) { opt1votes = _opt2votes; }
    void set_opt3votes(int _opt3votes) { opt1votes = _opt3votes; }
    void set_opt4votes(int _opt4votes) { opt1votes = _opt4votes; }

    void increase_opt1votes() { opt1votes++;}
    void increase_opt2votes() { opt2votes++;}
    void increase_opt3votes() { opt3votes++;}
    void increase_opt4votes() { opt4votes++;}

    int get_id() { return id; }
    string get_opt1msg() { return opt1msg; }
    string get_opt2msg() { return opt2msg; }
    string get_opt3msg() { return opt3msg; }
    string get_opt4msg() { return opt4msg; }
    int get_opt1votes() { return opt1votes; }
    int get_opt2votes() { return opt2votes; }
    int get_opt3votes() { return opt3votes; }
    int get_opt4votes() { return opt4votes; }

private:
    int id;
    string opt1msg;
    string opt2msg;
    string opt3msg;
    string opt4msg;
    int opt1votes;
    int opt2votes;
    int opt3votes;
    int opt4votes;
};

class Event {
public:
    void set_id(int _id) { id = _id; }
    void set_title(string _title) { title = _title; }
    void set_start(string _start) { title = _start; }
    void set_end(string _end) { title = _end; }
    void set_link_label(string _link_label) { title = _link_label; }
    void set_link(string _link) { title = _link; }

    int get_id() { return id; }
    string get_title() { return title; }
    string get_start() { return start; }
    string get_end() { return end; }
    string get_link_label() { return link_label; }
    string get_link() { return link; }

private:
    int id;
    string title;
    string start;
    string end;
    string link_label;
    string link;

};

class Image;
class Trade {
public:
    void set_id(int _id) { id = _id; }
    void set_pal_offer_id(int _id) { pal_offer_id = _id; }
    void set_offer_alt(string offer) { offer_alt = offer; }
    void set_pal_seek_id(int _id) { pal_seek_id = _id; }
    void set_seek_alt(string seek) { seek_alt = seek; }

    int get_id() { return id; }
    int get_pal_offer_id() { return pal_offer_id; }
    string get_offer_alt() { return offer_alt; }
    int get_pal_seek_id() { return pal_seek_id; }
    string get_seek_alt() { return seek_alt; }

private:
    int id;
    int pal_offer_id;
    string offer_alt;
    int pal_seek_id;
    string seek_alt;
};

class Post {

    friend class PostIO;

public:

    /**
     * @brief Post default constructor
     */
    Post();

    /**
     * @brief Post constructor for a post with given information
     * @param id      Identifier of the post
     * @param user    User who made the post
     * @param tag     Shoal tag of the post
     * @param message Test in the post
     * @param date    Date the post was sent
     */
    Post(int id, user::Account user, Shoal tag, std::string message,
         std::string date);

    void set_user(user::Account* u) { user = u; }
    void set_message(std::string m) { message = m; }
    void set_shoal(Shoal s) { shoal = s; }
    void set_survey(Survey* s) { survey = s; }
    void set_event(Event* e) { event = e; }
    void set_image(Image* i) { image = i; }
    void set_trade(Trade* t) { trade = t; }

    int get_id() { return id; }
    user::Account* get_user() { return user; }
    Shoal get_shoal() { return shoal; }
    std::string get_message() { return message; }
    std::string get_date() { return date; }
    Survey* get_survey() { return survey; }
    Event* get_event() { return event; }
    Image* get_image() { return image; }
    Trade* get_trade() { return trade; }

private:
    int id;
    user::Account* user;
    std::string message;
    std::string date;
    Shoal shoal;
    Survey* survey;
    Event* event;
    Image* image;
    Trade* trade;
};
} // namespace content

#endif // POST_H
