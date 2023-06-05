#include "reporter.h"

monitor::Reporter::Reporter(user::Account* user, db::MonitorDB* db):
    user(user),
    db(db)
{}

void monitor::Reporter::report(content::Post* p) {
    // users can't report themselves
    if (p->get_user()->get_id() == user->get_id()) return;
    db->report_post(p->get_id(), user->get_id());
}

void monitor::Reporter::report(chat::Message* m) {
    // users can't report themselves
    if (m->get_sender().get_id() == user->get_id()) return;
    db->report_message(m->get_id(), user->get_id());
}

void monitor::Reporter::report(profile::Profile* p) {
    // users can't report themselves
    if (p->get_id() == user->get_id()) return;
    db->report_profile(p->get_id(), user->get_id());
}
