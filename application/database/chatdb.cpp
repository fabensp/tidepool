#include "chatdb.h"

db::ChatDB::ChatDB(std::string file) : Database(file) {}

void db::ChatDB::fetch_chat(int chatId) {
    QString sqlcmd = "SELECT theme, title FROM chat WHERE id = :id;";
    query->prepare(sqlcmd);
    query->bindValue(":id", chatId);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ChatDB::fetch_chat_members(int chatId) {
    QString sqlcmd =
        "SELECT DISTINCT member_id FROM chat_membership WHERE chat_id = :id;";
    query->prepare(sqlcmd);
    query->bindValue(":id", chatId);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ChatDB::update_chat(int chatId, std::string title, int theme) {
    QString sqlcmd =
        "UPDATE chat SET title = :title, theme = :theme WHERE id = :id;";
    query->prepare(sqlcmd);
    query->bindValue(":title", QString::fromStdString(title));
    query->bindValue(":theme", theme);
    query->bindValue(":id", chatId);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ChatDB::create_chat_membership(int chat_id, int member_id) {
    QString sqlcmd =
        "insert into chat_membership (chat_id, member_id, unread) values "
        "(:chat_id, :member_id, 1) ON CONFLICT DO NOTHING;";
    query->prepare(sqlcmd);
    query->bindValue(":chat_id", chat_id);
    query->bindValue(":member_id", member_id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ChatDB::create_chat_membership(int chat_id, std::string member) {
    QString sqlcmd =
        "INSERT INTO chat_membership (chat_id, member_id, unread) SELECT "
        ":chat_id, id, 1 FROM user WHERE username = :member ON CONFLICT DO "
        "NOTHING;";
    query->prepare(sqlcmd);
    query->bindValue(":chat_id", chat_id);
    query->bindValue(":member", QString::fromStdString(member));
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ChatDB::remove_chat_membership(int chatId, int userId) {
    QString sqlcmd =
        "DELETE FROM chat_membership WHERE chat_id = :chatId AND member_id = "
        ":userId;";
    query->prepare(sqlcmd);
    query->bindValue(":chatId", chatId);
    query->bindValue(":userId", userId);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ChatDB::fetch_all_chats(int user_id) {
    QString sqlcmd =
        "SELECT c.id, c.theme, c.title, m.unread FROM chat as c, "
        "chat_membership AS m WHERE m.member_id = :user_id ORDER BY m.unread;";
    query->prepare(sqlcmd);
    query->bindValue(":user_id", user_id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ChatDB::fetch_num_chats(int userId, int n) {
    QString sqlcmd =
        "SELECT c.id, c.theme, c.title, m.unread FROM chat as c, "
        "chat_membership AS m WHERE m.member_id = :user_id AND c.id = m.chat_id "
    "GROUP BY c.title ORDER BY m.unread DESC LIMIT :n;";
    query->prepare(sqlcmd);
    query->bindValue(":user_id", userId);
    query->bindValue(":n", n);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ChatDB::insert_message(int id, int userId, int chatId,
                                std::string message) {
    QString sqlcmd =
        "INSERT INTO message (id, author_id, chat_id, message, send_date) "
        "VALUES (:id, :author_id, :chat_id, :message, DATETIME('now'));";
    query->prepare(sqlcmd);
    query->bindValue(":id", id);
    query->bindValue(":author_id", userId);
    query->bindValue(":chat_id", chatId);
    query->bindValue(":message", QString::fromStdString(message));
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ChatDB::remove_message(int id) {
    QString sqlcmd = "DELETE FROM message WHERE id = :id;";
    query->prepare(sqlcmd);
    query->bindValue(":id", id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ChatDB::insert_chat(int id, int theme, std::string title) {
    QString sqlcmd =
        "INSERT INTO chat (id, title, theme) VALUES (:id, :title, "
        ":theme);";
    query->prepare(sqlcmd);
    query->bindValue(":id", id);
    query->bindValue(":theme", theme);
    query->bindValue(":title", QString::fromStdString(title));
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ChatDB::remove_chat(int id) {
    QString sqlcmd = "DELETE FROM chat WHERE id = :id;";
    query->prepare(sqlcmd);
    query->bindValue(":id", id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ChatDB::pull_message(int msgId) {
    QString sqlcmd;
    sqlcmd = "SELECT author_id, message, ";
    sqlcmd += "CASE WHEN strftime('%Y','now') != strftime('%Y', send_date) ";
    sqlcmd += "THEN strftime('%m/%d/%Y', send_date) ";
    sqlcmd +=
        "WHEN strftime('%Y-%m-%d','now') != strftime('%Y-%m-%d', send_date) ";
    sqlcmd += "THEN strftime('%m/%d', send_date) ";
    sqlcmd += "ELSE strftime('%H:%M', send_date) END date ";
    sqlcmd += "FROM message WHERE id = :id;";
    query->prepare(sqlcmd);
    query->bindValue(":id", msgId);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ChatDB::pull_num_chat_messages(int chatId, int n) {
    QString sqlcmd;
    sqlcmd = "SELECT author_id, message, id, ";
    sqlcmd += "CASE WHEN strftime('%Y','now') != strftime('%Y', send_date) ";
    sqlcmd += "THEN strftime('%m/%d/%Y', send_date) ";
    sqlcmd +=
        "WHEN strftime('%Y-%m-%d','now') != strftime('%Y-%m-%d', send_date) ";
    sqlcmd += "THEN strftime('%m/%d', send_date) ";
    sqlcmd += "ELSE strftime('%H:%M', send_date) END date ";
    sqlcmd +=
        "FROM message WHERE chat_id = :chat_id ORDER BY id DESC LIMIT :n;";
    query->prepare(sqlcmd);
    query->bindValue(":chat_id", chatId);
    query->bindValue(":n", n);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}
void db::ChatDB::set_read(int chatId, int userId) {
    QString sqlcmd =
        "UPDATE OR IGNORE chat_membership SET unread = 0 "
        "WHERE chat_id = :c AND member_id = :u;";
    query->prepare(sqlcmd);
    query->bindValue(":c", chatId);
    query->bindValue(":u", userId);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ChatDB::set_unread(int chatId) {
    QString sqlcmd =
        "UPDATE OR IGNORE chat_membership SET unread = 1 WHERE chat_id = :c;";
    query->prepare(sqlcmd);
    query->bindValue(":c", chatId);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ChatDB::max_chatId() {
    QString sqlcmd = "SELECT MAX(id) FROM chat;";
    if (query->exec(sqlcmd) == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ChatDB::max_messageId() {
    QString sqlcmd = "SELECT MAX(id) FROM message;";
    if (query->exec(sqlcmd) == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}
