
#include "monitordb.h"

namespace db {

MonitorDB::MonitorDB(std::string file) : Database(file) {}

void MonitorDB::fetch_posts_equijoined(QString filter, QString search, int r) {
    QString sqlcmd;
    sqlcmd +=
        "SELECT ps.id, a.id, COUNT(*) FILTER (WHERE r.post_id = ps.id), "
        "a.username ";
    sqlcmd += "FROM user AS a, ";
    sqlcmd += "post_report AS r, ";
    sqlcmd += "post AS ps, ";
    sqlcmd += "profile AS pr ";
    sqlcmd += "WHERE a.id = ps.creator_id ";
    sqlcmd += "AND a.id = pr.user_id ";
    if (r) sqlcmd += "AND ps.id = r.post_id ";
    if (search != "") sqlcmd += "AND " + filter + search;
    sqlcmd += " GROUP BY ps.id ORDER BY COUNT(*) DESC ";
    sqlcmd += "LIMIT 20;";
    query->prepare(sqlcmd);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}
void MonitorDB::fetch_messages_equijoined(QString filter, QString search,
                                          int r) {
    QString sqlcmd;
    sqlcmd +=
        "SELECT m.id, a.id, COUNT(*) FILTER (WHERE r.message_id = m.id), "
        "a.username ";
    sqlcmd += "FROM user AS a, ";
    sqlcmd += "message_report AS r, ";
    sqlcmd += "message AS m, ";
    sqlcmd += "chat AS c, ";
    sqlcmd += "profile AS p ";
    sqlcmd += "WHERE a.id = m.author_id ";
    sqlcmd += "AND m.chat_id = c.id ";
    sqlcmd += "AND a.id = p.user_id ";
    if (r) sqlcmd += "AND m.id = r.message_id ";
    if (search != "") sqlcmd += "AND " + filter + search;
    sqlcmd += " GROUP BY m.id ORDER BY COUNT(*) DESC ";
    sqlcmd += "LIMIT 20;";
    if (query->exec(sqlcmd) == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void MonitorDB::fetch_profiles_equijoined(QString filter, QString search,
                                          int r) {
    QString sqlcmd;
    sqlcmd +=
        "SELECT a.id, a.id, COUNT(*) FILTER (WHERE r.reported_user_id = a.id), "
        "a.username ";
    sqlcmd += "FROM user AS a, ";
    sqlcmd += "profile_report AS r, ";
    sqlcmd += "profile AS p ";
    sqlcmd += "WHERE a.id = p.user_id ";
    sqlcmd += "AND a.access != 0 ";
    if (r) sqlcmd += "AND a.id = r.reported_user_id ";
    if (search != "") sqlcmd += "AND " + filter + search;
    sqlcmd += " GROUP BY a.id ORDER BY COUNT(*) DESC ";
    sqlcmd += "LIMIT 20;";
    query->prepare(sqlcmd);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void MonitorDB::report_post(int postId, int reporterId) {
    QString sqlcmd;
    sqlcmd +=
        "INSERT INTO post_report (post_id, reporter_id) VALUES (:p, :r) "
        "ON CONFLICT DO NOTHING;";
    query->prepare(sqlcmd);
    query->bindValue(":p", postId);
    query->bindValue(":r", reporterId);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void MonitorDB::report_message(int messageId, int reporterId) {
    QString sqlcmd;
    sqlcmd +=
        "INSERT INTO message_report (message_id, reporter_id) VALUES (:m, :r) "
        "ON CONFLICT DO NOTHING;";
    query->prepare(sqlcmd);
    query->bindValue(":m", messageId);
    query->bindValue(":r", reporterId);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void MonitorDB::report_profile(int toId, int fromId) {
    QString sqlcmd;
    sqlcmd +=
        "INSERT INTO profile_report (reported_user_id, reporter_id) "
        "VALUES (:t, :f) ON CONFLICT DO NOTHING;";
    query->prepare(sqlcmd);
    query->bindValue(":t", toId);
    query->bindValue(":f", fromId);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void MonitorDB::unreport_post(int id) {
    QString sqlcmd = "DELETE FROM post_report WHERE post_id = :id;";
    query->prepare(sqlcmd);
    query->bindValue(":id", id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void MonitorDB::unreport_message(int id) {
    QString sqlcmd = "DELETE FROM message_report WHERE message_id = :id;";
    query->prepare(sqlcmd);
    query->bindValue(":id", id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void MonitorDB::unreport_profile(int id) {
    QString sqlcmd = "DELETE FROM profile_report WHERE reported_user_id = :id;";
    query->prepare(sqlcmd);
    query->bindValue(":id", id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

} // namespace db
