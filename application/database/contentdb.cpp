
#include "contentdb.h"

namespace db {

void ContentDB::fetch_post(int id) {
    QString sqlcmd =
        "SELECT creator_id, shoal_tag, message, strftime('%m/%d/%Y %H:%M', "
        "post_date), image_id, trade_id, survey_id, event_id FROM post WHERE "
        "id = :id;";
    query->prepare(sqlcmd);
    query->bindValue(":id", id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void ContentDB::fetch_trade(int id) {
    QString sqlcmd =
        "SELECT pal_offer_id, offer_alt, pal_seek_id, seek_alt "
        "FROM trade WHERE id = :id;";
    query->prepare(sqlcmd);
    query->bindValue(":id", id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void ContentDB::fetch_survey(int id) {
    QString sqlcmd = "SELECT opt1msg, opt2msg, opt3msg, opt4msg, "
                     "opt1votes, opt2votes, opt3votes, opt4votes "
                     "FROM survey WHERE id =:id;";
    query->prepare(sqlcmd);
    query->bindValue(":id", id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void ContentDB::fetch_event(int id) {
    QString sqlcmd = "SELECT title, start, end, link_label, link "
                     "FROM survey WHERE id = :id;";
    query->prepare(sqlcmd);
    query->bindValue(":id", id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void ContentDB::insert_post(int id, int creator_id, std::string shoal_tag,
                            std::string message, int iid, int tid, int sid,
                            int eid) {
    QString sqlcmd =
        "INSERT INTO post (id, creator_id, shoal_tag, message, post_date, "
        "image_id, trade_id, survey_id, event_id) VALUES (:id, :creator_id, "
        ":shoal_tag, :message, DATETIME('now'), :iid, :tid, :sid, :eid);";
    query->prepare(sqlcmd);
    query->bindValue(":id", id);
    query->bindValue(":creator_id", creator_id);
    query->bindValue(":shoal_tag", QString::fromStdString(shoal_tag));
    query->bindValue(":message", QString::fromStdString(message));
    query->bindValue(":iid", (iid < 0) ? QMetaType::Int : iid);
    query->bindValue(":tid", (tid < 0) ? QMetaType::Int : tid);
    query->bindValue(":sid", (sid < 0) ? QMetaType::Int : sid);
    query->bindValue(":eid", (eid < 0) ? QMetaType::Int : eid);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void ContentDB::remove_post(int id) {
    QString sqlcmd = "DELETE FROM post WHERE id = :id;";
    query->prepare(sqlcmd);
    query->bindValue(":id", id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void ContentDB::fetch_shoal(std::string tag) {
    QString sqlcmd =
        "SELECT theme, description, creator_id FROM shoal WHERE tag = :tag;";
    query->prepare(sqlcmd);
    query->bindValue(":tag", QString::fromStdString(tag));
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void ContentDB::fetch_user_shoals(int id) {
    QString sqlcmd =
        "SELECT tag, theme, description, creator_id FROM shoal WHERE tag IN "
        "(SELECT shoal_tag FROM shoal_membership WHERE member_id = :id);";
    query->prepare(sqlcmd);
    query->bindValue(":id", id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void ContentDB::pull_num_reef_posts(int userId, int n, int offset) {
    QString sqlcmd =
        "SELECT id, creator_id, shoal_tag, message, strftime('%m/%d/%Y %H:%M', "
        "post_date), image_id, trade_id, survey_id, event_id FROM post WHERE "
        "creator_id IN (SELECT to_user_id FROM reef WHERE from_user_id = "
        ":user_id) OR creator_id = :user_id ORDER BY id DESC LIMIT :n OFFSET "
        ":o;";
    query->prepare(sqlcmd);
    query->bindValue(":user_id", userId);
    query->bindValue(":n", n);
    query->bindValue(":o", offset);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void ContentDB::pull_num_user_shoal_posts(int userId, int n, int offset) {
    QString sqlcmd =
        "SELECT id, creator_id, shoal_tag, message, strftime('%m/%d/%Y %H:%M', "
        "post_date), image_id, trade_id, survey_id, event_id FROM post WHERE "
        "shoal_tag IN (SELECT shoal_tag FROM shoal_membership WHERE member_id "
        "= :user_id) ORDER BY id DESC LIMIT :n OFFSET :o;";
    query->prepare(sqlcmd);
    query->bindValue(":user_id", userId);
    query->bindValue(":n", n);
    query->bindValue(":o", offset);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void ContentDB::pull_num_shoal_posts(std::string tag, int n, int offset) {
    QString sqlcmd =
        "SELECT id, creator_id, shoal_tag, message, strftime('%m/%d/%Y %H:%M', "
        "post_date), image_id, trade_id, survey_id, event_id FROM post WHERE "
        "shoal_tag = :tag ORDER BY id DESC LIMIT :n OFFSET :o;";
    query->prepare(sqlcmd);
    query->bindValue(":tag", QString::fromStdString(tag));
    query->bindValue(":n", n);
    query->bindValue(":o", offset);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void ContentDB::pull_num_user_posts(int userId, int n, int offset) {
    QString sqlcmd =
        "SELECT id, shoal_tag, message, strftime('%m/%d/%Y %H:%M', "
        "post_date), image_id, trade_id, survey_id, event_id FROM post WHERE "
        "creator_id = :user_id ORDER BY id DESC LIMIT :n OFFSET :o;";
    query->prepare(sqlcmd);
    query->bindValue(":user_id", userId);
    query->bindValue(":n", n);
    query->bindValue(":o", offset);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void ContentDB::insert_trade(int id, int pal_offer_id, std::string offer_alt, int pal_seek_id, std::string seek_alt) {
    QString sqlcmd = "INSERT INTO trade (id, pal_offer_id, offer_alt, pal_seek_id, seek_alt) "
                     "VALUES (:id, :pal_offer_id, :offer_alt, :pal_seek_id, :seek_alt);";
    query->prepare(sqlcmd);
    query->bindValue(":id", id);
    query->bindValue(":pal_offer_id", pal_offer_id);
    query->bindValue(":offer_alt", QString::fromStdString(offer_alt));
    query->bindValue(":pal_seek_id", pal_seek_id);
    query->bindValue(":seek_alt", QString::fromStdString(seek_alt));
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void ContentDB::insert_survey(int id, std::string opt1msg, std::string opt2msg,
                              std::string opt3msg, std::string opt4msg) {
    QString sqlcmd = "INSERT INTO survey (id, opt1msg, opt2msg, opt3msg, opt4msg, "
                     "opt1votes, opt2votes, opt3votes, opt4votes VALUES (:id, "
                     ":opt1msg, :opt2msg, :opt3msg, :opt4msg, :opt1votes, :opt2votes, "
                     ":opt3votes, :opt4votes);";
    query->prepare(sqlcmd);
    query->bindValue(":id", id);
    query->bindValue(":opt1msg", QString::fromStdString(opt1msg));
    query->bindValue(":opt2msg", QString::fromStdString(opt2msg));
    query->bindValue(":opt3msg", QString::fromStdString(opt3msg));
    query->bindValue(":opt4msg", QString::fromStdString(opt4msg));
    query->bindValue(":opt1votes", 0);
    query->bindValue(":opt2votes", 0);
    query->bindValue(":opt3votes", 0);
    query->bindValue(":opt4votes", 0);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void ContentDB::insert_event(int id, std::string title, std::string start, std::string end, std::string link_label, std::string link) {
    QString sqlcmd = "INSERT INTO event (id, title, start, end, link_label, link VALUES (:id, :title, :start, :end, :link_label, :link;";
    query->prepare(sqlcmd);
    query->bindValue(":id", id);
    query->bindValue(":title", QString::fromStdString(title));
    query->bindValue(":start", QString::fromStdString(start));
    query->bindValue(":end", QString::fromStdString(end));
    query->bindValue(":link_label", QString::fromStdString(link_label));
    query->bindValue(":link", QString::fromStdString(link));
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void ContentDB::max_postid() {
    QString sqlcmd = "SELECT MAX(id) FROM post;";
    query->prepare(sqlcmd);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void ContentDB::max_tradeid() {
    QString sqlcmd = "SELECT MAX(id) FROM trade;";
    query->prepare(sqlcmd);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void ContentDB::max_surveyid() {
    QString sqlcmd = "SELECT MAX(id) FROM survey;";
    query->prepare(sqlcmd);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void ContentDB::max_eventid() {
    QString sqlcmd = "SELECT MAX(id) FROM event;";
    query->prepare(sqlcmd);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void ContentDB::create_shoal(std::string tag, int theme, std::string desc,
                             int cid) {
    QString sqlcmd = "INSERT INTO shoal VALUES(:ta, :th, :d, :id);";
    query->prepare(sqlcmd);
    query->bindValue(":ta", QString::fromStdString(tag));
    query->bindValue(":th", theme);
    query->bindValue(":d", QString::fromStdString(desc));
    query->bindValue(":id", cid);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

} // namespace db
