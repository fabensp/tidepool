
#include "reportaggregator.h"

monitor::ReportAggregator::ReportAggregator(user::Account* user,
                                            db::Database* db) :
    user(user),
    mdb((db::MonitorDB*)db) {}

std::vector<monitor::MonitorItem*>
monitor::ReportAggregator::fetch_among_posts(int f, std::string s, int r) {
    QString filter;
    QString search = QString::fromStdString(s);

    // for things that are strings, enclose the search in quotes
    if (f != 2 && f != 4 && search != "") search = '\'' + search + '\'';

    switch (f) {
    case 0: filter = "a.username = "; break;      // username
    case 1: filter = "a.email = "; break;         // email
    case 2: filter = "a.id = "; break;            // user id
    case 3: filter = "pr.display_name = "; break; // display name
    case 4:
        filter = "ps.message LIKE "; // post body content phrase
        search = "'%" + search + "%'";
        break;
    case 5: filter = "ps.shoal_tag = "; break;                  // shoal tag
    case 6: filter = "strftime('%m/%d/%Y', ps.date) = "; break; // post date
    }
    mdb->fetch_posts_equijoined(filter, search, r);

    std::vector<MonitorItem*> out;
    while (mdb->next()) {
        MonitorItem* i;
        i = new MonitorItem(mdb->result()->value(0).toInt(),
                            mdb->result()->value(1).toInt(),
                            mdb->result()->value(2).toInt(),
                            mdb->result()->value(3).toString().toStdString());
        out.push_back(i);
    }
    return out;
}

std::vector<monitor::MonitorItem*>
monitor::ReportAggregator::fetch_among_messages(int f, std::string s, int r) {
    QString filter;
    QString search = QString::fromStdString(s);

    // for things that are strings, enclose the search in quotes
    if (f != 2 && f != 4 && f != 5 && search != "")
        search = '\'' + search + '\'';

    switch (f) {
    case 0: filter = "a.username = "; break;     // username
    case 1: filter = "a.email = "; break;        // email
    case 2: filter = "a.id = "; break;           // user id
    case 3: filter = "p.display_name = "; break; // display name
    case 4:
        filter = "m.message LIKE "; // message content phrase
        search = "'%" + search + "%'";
        break;
    case 5: filter = "c.id = "; break;                         // chat id
    case 6: filter = "c.title = "; break;                      // chat title
    case 7: filter = "strftime('%m/%d/%Y', m.date) = "; break; // send date
    }

    mdb->fetch_messages_equijoined(filter, search, r);

    std::vector<MonitorItem*> out;
    while (mdb->next()) {
        MonitorItem* i;
        i = new MonitorItem(mdb->result()->value(0).toInt(),
                            mdb->result()->value(1).toInt(),
                            mdb->result()->value(2).toInt(),
                            mdb->result()->value(3).toString().toStdString());
        out.push_back(i);
    }
    return out;
}

std::vector<monitor::MonitorItem*>
monitor::ReportAggregator::fetch_among_profiles(int f, std::string s, int r) {
    QString filter;
    QString search = QString::fromStdString(s);

    // for things that are strings, enclose the search in quotes
    if (f != 2 && f != 4 && search != "") search = '\'' + search + '\'';

    switch (f) {
    case 0: filter = "a.username = "; break;     // username
    case 1: filter = "a.email = "; break;        // email
    case 2: filter = "a.id = "; break;           // user id
    case 3: filter = "p.display_name = "; break; // display name
    case 4:
        filter = "p.bio LIKE "; // bio phrase
        search = "'%" + search + "%'";
        break;
    }
    mdb->fetch_profiles_equijoined(filter, search, r);

    std::vector<MonitorItem*> out;
    while (mdb->next()) {
        MonitorItem* i;
        i = new MonitorItem(mdb->result()->value(0).toInt(),
                            mdb->result()->value(1).toInt(),
                            mdb->result()->value(2).toInt(),
                            mdb->result()->value(3).toString().toStdString());
        out.push_back(i);
    }
    return out;
}

int monitor::ReportAggregator::unreport_post(content::Post& p,
                                             user::Account& admin) {
    if (admin.get_access() < 32 || !admin.get_verified()) return 0;
    mdb->unreport_post(p.get_id());
    return 1;
}

int monitor::ReportAggregator::unreport_message(chat::Message& m,
                                                user::Account& admin) {
    if (admin.get_access() < 32 || !admin.get_verified()) return 0;
    mdb->unreport_message(m.get_id());
    return 1;
}

int monitor::ReportAggregator::unreport_profile(user::Account& a,
                                                user::Account& admin) {
    if (admin.get_access() < 32 || !admin.get_verified()) return 0;
    mdb->unreport_profile(a.get_id());
    return 1;
}
