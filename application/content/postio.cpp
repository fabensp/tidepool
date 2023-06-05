
#include "postio.h"

namespace content {

/**
 * @brief PostIO constructor that links to the content database
 * @param db Profile database
 */
PostIO::PostIO(db::ContentDB* db) : db(db), aio((db::UserDB*)db) {}

/**
 * @brief remove_post removes a post from the application
 * @param p     Post to remove
 * @param admin The admin that initiated the remove
 * @return 1 if successful, 0 if not
 */
int PostIO::remove_post(Post& p, user::Account& admin) {
    if (admin.get_access() < 32 || !admin.get_verified()) return 0;
    db->remove_post(p.get_id());
    return 1;
}

/**
 * @brief pull_post pulls a post from the database
 * @param p  Post to push the info into
 * @param id identifier of the post to pull
 * @return 1 if successful, 0 if not
 */
int PostIO::pull_post(Post& p, int id) {
    db->fetch_post(id);
    int user_id = -1;
    std::string shoal_tag;
    if (db->next()) {
        p.id = id;
        user_id = db->result()->value(0).toInt();
        shoal_tag = db->result()->value(1).toString().toStdString();
        p.message = db->result()->value(2).toString().toStdString();
        p.date = db->result()->value(3).toString().toStdString();
        /*
         * TODO ADDONS
         */
    } else return 0;
    db->fetch_shoal(shoal_tag);
    if (db->next()) {
        p.shoal.tag = shoal_tag;
        p.shoal.theme = db->result()->value(0).toInt();
        p.shoal.description = db->result()->value(1).toString().toStdString();
    } else return 0;
    p.user = new user::Account();
    if (!aio.pull(*p.user, user_id)) {
        delete p.user;
        return 0;
    }
    return 1;
}

/**
 * @brief insert_post insert a post into the database
 * @param p Post to insert
 * @return 1 if successful, 0 if not
 */
int PostIO::insert_post(Post& p) {
    if (!p.user->get_verified()) return 0;
    int id = next_id();
    int iid = (p.get_image() != nullptr) ? /*p.get_image()->get_id()*/ -1 : -1;
    int tid = (p.get_image() != nullptr) ? /*p.get_trade()->get_id()*/ -1 : -1;
    int sid = (p.get_image() != nullptr) ? /*p.get_survey()->get_id()*/ -1 : -1;
    int eid = (p.get_image() != nullptr) ? /*p.get_event()->get_id()*/ -1 : -1;
    db->insert_post(id, p.get_user()->get_id(), p.shoal.get_tag(),
                    p.get_message(), iid, tid, sid, eid);
    p.id = id;
    return 1;
}

/**
 * @brief pull_num_reef_posts pull a certain number of posts from a users reef
 * @param user   User to pull reef posts for
 * @param n      Number of posts to pull
 * @param offset Where to start pulling from
 * @return 1 if successful, 0 if not
 */
std::vector<Post*> PostIO::pull_num_reef_posts(user::Account* user, int n,
                                               int offset) {
    std::vector<Post*> out;
    db->pull_num_reef_posts(user->get_id(), n, offset);
    std::vector<int> ids;
    while (db->next()) {
        Post* p = new Post();
        p->id = db->result()->value(0).toInt();
        ids.push_back(db->result()->value(1).toInt());
        p->shoal.tag = db->result()->value(2).toString().toStdString();
        p->message = db->result()->value(3).toString().toStdString();
        p->date = db->result()->value(4).toString().toStdString();
        /*
         * TODO ADDONS
         */
        out.push_back(p);
    }
    int i = 0;
    for (Post* p : out) {
        p->user = new user::Account();
        aio.pull(*p->user, ids[i++]);
        db->fetch_shoal(p->shoal.tag);
        if (db->next()) {
            p->shoal.theme = db->result()->value(0).toInt();
            p->shoal.description =
                db->result()->value(1).toString().toStdString();
        }
    }
    return out;
}

/**
 * @brief pull_num_shoal_posts pull a certain number of posts from a users shoal
 * @param user   User to pull shoal posts for
 * @param n      Number of posts to pull
 * @param offset Where to start pulling from
 * @return 1 if successful, 0 if not
 */
std::vector<Post*> PostIO::pull_num_user_shoal_posts(user::Account* user, int n,
                                                     int offset) {
    std::vector<Post*> out;
    db->pull_num_user_shoal_posts(user->get_id(), n, offset);
    std::vector<int> ids;
    while (db->next()) {
        Post* p = new Post();
        p->id = db->result()->value(0).toInt();
        ids.push_back(db->result()->value(1).toInt());
        p->shoal.tag = db->result()->value(2).toString().toStdString();
        p->message = db->result()->value(3).toString().toStdString();
        p->date = db->result()->value(4).toString().toStdString();
        /*
         * TODO ADDONS
         */
        out.push_back(p);
    }
    int i = 0;
    for (Post* p : out) {
        p->user = new user::Account();
        aio.pull(*p->user, ids[i++]);
        db->fetch_shoal(p->shoal.tag);
        if (db->next()) {
            p->shoal.theme = db->result()->value(0).toInt();
            p->shoal.description =
                db->result()->value(1).toString().toStdString();
        }
    }
    return out;
}

/**
 * @brief pull_num_shoal_posts pull a certain number of posts from a given shoal
 * @param s      Shoal to pull posts from
 * @param n      Number of posts to pull
 * @param offset Where to start pulling posts from
 * @return 1 if successful, 0 if not
 */
std::vector<Post*> PostIO::pull_num_shoal_posts(Shoal s, int n, int offset) {
    std::vector<Post*> out;
    db->pull_num_shoal_posts(s.get_tag(), n, offset);
    std::vector<int> ids;
    while (db->next()) {
        Post* p = new Post();
        p->id = db->result()->value(0).toInt();
        ids.push_back(db->result()->value(1).toInt());
        p->shoal = s;
        p->message = db->result()->value(3).toString().toStdString();
        p->date = db->result()->value(4).toString().toStdString();
        /*
         * TODO ADDONS
         */
        out.push_back(p);
    }
    int i = 0;
    for (Post* p : out) {
        p->user = new user::Account();
        aio.pull(*p->user, ids[i++]);
    }
    return out;
}

/**
 * @brief pull_num_user_posts pulls a certain number of posts from a given user
 * @param user   User to pull posts of
 * @param n      Number of posts to pull
 * @param offset Where to start pulling posts from
 * @return 1 if successful, 0 if not
 */
std::vector<Post*> PostIO::pull_num_user_posts(user::Account* user, int n,
                                               int offset) {
    std::vector<Post*> out;
    db->pull_num_user_posts(user->get_id(), n, offset);
    while (db->next()) {
        Post* p = new Post();
        p->id = db->result()->value(0).toInt();
        p->user = user;
        p->shoal.tag = db->result()->value(1).toString().toStdString();
        p->message = db->result()->value(2).toString().toStdString();
        p->date = db->result()->value(3).toString().toStdString();
        /*
         * TODO ADDONS
         */
        out.push_back(p);
    }
    for (Post* p : out) {
        db->fetch_shoal(p->shoal.tag);
        if (db->next()) {
            p->shoal.theme = db->result()->value(0).toInt();
            p->shoal.description =
                db->result()->value(1).toString().toStdString();
        }
    }
    return out;
}

/**
 * @brief pull_user_shoals Pull all the shoals that belong to a given user
 * @param user Users who shoals to pull from
 * @return 1 if successful, 0 if not
 */
std::vector<Shoal*> PostIO::pull_user_shoals(user::Account* user) {
    std::vector<Shoal*> out;
    db->fetch_user_shoals(user->get_id());
    while (db->next()) {
        Shoal* s = new Shoal();
        s->tag = db->result()->value(0).toString().toStdString();
        s->theme = db->result()->value(1).toInt();
        s->description = db->result()->value(2).toString().toStdString();
        s->creator_id = db->result()->value(3).toInt();
        out.push_back(s);
    }
    return out;
}

/**
 * @brief pull_trade pull a trade from the database
 * @param t  Trade to push info into
 * @param id Identifier of the trade
 * @return 1 if successful, 0 if not
 */
int PostIO::pull_trade(Trade& t, int id) {
    if (id < 0) return 0;

    db->fetch_trade(id);
    if (db->next()) {
        t.set_id(id);
        t.set_pal_offer_id(db->result()->value("pal_offer_id").toInt());
        t.set_offer_alt(db->result()->value("offer_alt").toString().toStdString());
        t.set_pal_seek_id(db->result()->value("pal_seek_id").toInt());
        t.set_seek_alt(db->result()->value("seek_alt").toString().toStdString());
    } else return 0;
    return 1;
}

/**
 * @brief create_trade create a new trade given information
 * @param p            Post to load info into
 * @param pal_offer_id Identifier for the pal being offered
 * @param offer_alt    Text to go along with the offer
 * @param pal_seek_id  Identifier for the pal on the trade block
 * @param seek_alt     Text to go along with the pal on the trade block
 * @return 1 if successful, 0 if not
 */
int PostIO::create_trade(Post& p, int pal_offer_id, string offer_alt, int pal_seek_id, string seek_alt) {
    if (p.get_id() < 0 ||pal_offer_id < 0 || pal_seek_id < 0) return 0;
    int id = next_trade_id();
    db->insert_trade(id, pal_offer_id, offer_alt, pal_seek_id, seek_alt);
    Trade* t = new Trade();
    t->set_id(id);
    t->set_pal_offer_id(pal_offer_id);
    t->set_offer_alt(offer_alt);
    t->set_pal_offer_id(pal_seek_id);
    t->set_seek_alt(seek_alt);
    p.set_trade(t);
    return 1;
}

/**
 * @brief pull_survey pull a survey from the database
 * @param s  Survey to push info into
 * @param id Identifier of the survey
 * @return 1 if successful, 0 if not
 */
int PostIO::pull_survey(Survey& s, int id) {
    if (id < 0) return 0;

    db->fetch_survey(id);
    if (db->next()) {
        s.set_id(id);
        s.set_opt1msg(db->result()->value("opt1msg").toString().toStdString());
        s.set_opt2msg(db->result()->value("opt2msg").toString().toStdString());
        s.set_opt3msg(db->result()->value("opt3msg").toString().toStdString());
        s.set_opt4msg(db->result()->value("opt4msg").toString().toStdString());
        s.set_opt1votes(db->result()->value("opt1votes").toInt());
        s.set_opt2votes(db->result()->value("opt2votes").toInt());
        s.set_opt3votes(db->result()->value("opt3votes").toInt());
        s.set_opt4votes(db->result()->value("opt4votes").toInt());
    } else return 0;
    return 1;
}

/**
 * @brief create_survey Create a survey with the given information
 * @param p       Post to load the survey into
 * @param opt1msg Label for option 1
 * @param opt2msg Label for option 2
 * @param opt3msg Label for option 3
 * @param opt4msg Label for option 4
 * @return 1 if successful, 0 if not
 */
int PostIO::create_survey(Post&p, string opt1msg, string opt2msg, string opt3msg, string opt4msg) {
    if (p.get_id() < 0) return 0;
    int id = next_survey_id();
    db->insert_survey(id, opt1msg, opt2msg, opt3msg, opt4msg);
    Survey* s = new Survey();
    s->set_opt1msg(opt1msg);
    s->set_opt2msg(opt2msg);
    s->set_opt3msg(opt3msg);
    s->set_opt4msg(opt4msg);
    s->set_opt1votes(0);
    s->set_opt2votes(0);
    s->set_opt3votes(0);
    s->set_opt4votes(0);
    p.set_survey(s);
    return 1;
}

/**
 * @brief pull_event pull an event from the database
 * @param e  Event to push info into
 * @param id Identifier of the event
 * @return 1 if successful, 0 if not
 */
int PostIO::pull_event(Event& e, int id) {
    if (id < 0) return 0;

    db->fetch_event(id);
    if (db->next()) {
        e.set_id(id);
        e.set_title(db->result()->value("title").toString().toStdString());
        e.set_start(db->result()->value("start").toString().toStdString());
        e.set_end(db->result()->value("end").toString().toStdString());
        e.set_link_label(db->result()->value("link_label").toString().toStdString());
        e.set_link(db->result()->value("link").toString().toStdString());
    } else return 0;
    return 1;
}

/**
 * @brief create_event create an event with the given information
 * @param p          Post to event load info into
 * @param title      Title of the event
 * @param start      Start time of the event
 * @param end        End time of the event
 * @param link_label Label of the link of the event website
 * @param link       Link to the event website
 * @return 1 if successful, 0 if not
 */
int PostIO::create_event(Post&p, string title, string start, string end, string link_label, string link) {
    if (p.get_id() < 0) return 0;
    int id = next_event_id();
    db->insert_event(id, title, start, end, link_label, link);
    Event* e = new Event();
    e->set_id(id);
    e->set_title(title);
    e->set_start(start);
    e->set_end(end);
    e->set_link_label(link_label);
    e->set_link(link);
    p.set_event(e);
    return 1;
}

/**
 * @brief create_shoal create a shoal in the database with the information
 * @param s Shoal to put into database
 * @return 1 if successful, 0 if not
 */
int PostIO::create_shoal(Shoal* s) {
    db->create_shoal(s->get_tag(), s->get_theme(), s->get_description(),
                     s->get_creator_id());
}

/**
 * @brief next_id find the next highest id for a post
 * @return the next id that can be used for a post
 */
int PostIO::next_id() {
    db->max_postid();
    // "SELECT MAX(id) FROM post;"
    int num;
    if (db->next()) {
        num = db->result()->value(0).toInt();
    } else return -100;
    int id = num + 1;
    return id;
}

/**
 * @brief next_trade_id find the next highest id for a trade
 * @return the next id that can be used for a trade
 */
int PostIO::next_trade_id() {
    db->max_tradeid();

    int num;
    if (db->next()) {
        num = db->result()->value(0).toInt();
    } else return -100;
    int id = num + 1;
    return id;
}

/**
 * @brief next_survey_id find the next highest id for a survey
 * @return the next id that can be used for a survey
 */
int PostIO::next_survey_id() {
    db->max_surveyid();

    int num;
    if (db->next()) {
        num = db->result()->value(0).toInt();
    } else return -100;
    int id = num + 1;
    return id;
}

/**
 * @brief next_event_id find the next highest id for a event
 * @return the next id that can be used for a event
 */
int PostIO::next_event_id() {
    db->max_eventid();

    int num;
    if (db->next()) {
        num = db->result()->value(0).toInt();
    } else return -100;
    int id = num + 1;
    return id;
}

} // namespace content

