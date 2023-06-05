#include "userdb.h"

db::UserDB::UserDB(std::string file) : Database(file) {}

void db::UserDB::fetch_user(int id) {
    QString sqlcmd = "";
    sqlcmd = "SELECT username, email, access ";
    sqlcmd += "FROM user WHERE id = :id;";
    query->prepare(sqlcmd);
    query->bindValue(":id", id);
    // execute the provided sql call
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::UserDB::fetch_user_username(std::string username) {
    QString sqlcmd = "";
    sqlcmd = "SELECT id, email, access FROM user WHERE username = :u;";
    query->prepare(sqlcmd);
    query->bindValue(":u", QString::fromStdString(username));
    // execute the provided sql call
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::UserDB::fetch_user_email(std::string email) {
    QString sqlcmd = "";
    sqlcmd = "SELECT id, username, access FROM user WHERE email = :e;";
    query->prepare(sqlcmd);
    query->bindValue(":e", QString::fromStdString(email));
    // execute the provided sql call
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::UserDB::fetch_guardian(int id) {
    QString sqlcmd =
        "SELECT child_id, guardian_id FROM guardian WHERE child_id = :id;";
    query->prepare(sqlcmd);
    query->bindValue(":id", id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::UserDB::fetch_unapproved() {
    QString sqlcmd = "SELECT id FROM user WHERE (access & 8) = 8;";
    query->prepare(sqlcmd);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::UserDB::check_user(std::string username, std::string email, int id) {
    QString sqlcmd =
        "SELECT COUNT(username = :username), COUNT(email = :email) FROM user "
        "WHERE id != :id AND (username = :username OR email = :email);";
    query->prepare(sqlcmd);
    query->bindValue(":username", QString::fromStdString(username));
    query->bindValue(":email", QString::fromStdString(email));
    query->bindValue(":id", id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::UserDB::insert_user(int id, std::string username, std::string email,
                             std::string password, int access) {
    QString sqlcmd =
            "INSERT INTO user (id, username, email, password, access) VALUES (:id, "
            ":username, :email, :password, :access);";
    query->prepare(sqlcmd);
    query->bindValue(":id", id);
    query->bindValue(":username", QString::fromStdString(username));
    query->bindValue(":email", QString::fromStdString(email));
    query->bindValue(":password", QString::fromStdString(password));
    query->bindValue(":access", access);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::UserDB::update_user(int id, std::string username, std::string email,
                             std::string password, int access) {
    QString sqlcmd = "UPDATE user SET username = :username, email = :email";
    if (password != "") sqlcmd += ", password = :password";
    if (access != -1) sqlcmd += ", access = :access";
    sqlcmd += " WHERE id = :id;";

    query->prepare(sqlcmd);
    query->bindValue(":username", QString::fromStdString(username));
    query->bindValue(":email", QString::fromStdString(email));
    query->bindValue(":id", id);
    if (password != "")
        query->bindValue(":password", QString::fromStdString(password));
    if (access != -1) query->bindValue(":access", access);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::UserDB::verify_user(std::string email, std::string password) {

    QString sqlcmd = "";
    sqlcmd = "SELECT id, username, access ";
    sqlcmd += "FROM user";
    sqlcmd += " WHERE email = '";
    sqlcmd += QString::fromStdString(email);
    sqlcmd += "' AND password = '";
    sqlcmd += QString::fromStdString(password);
    sqlcmd += "';";

    query->prepare(sqlcmd);
    if(query->exec(sqlcmd) == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::UserDB::insert_guardian(int child_id, int guardian_id) {
    QString sqlcmd =
            "INSERT INTO guardian (child_id, guardian_id) VALUES (:child_id, "
            ":guardian_id);";
    query->prepare(sqlcmd);
    query->bindValue(":child_id", child_id);
    query->bindValue(":guardian_id", guardian_id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::UserDB::update_guardian(int id, int guardian_id) {
    QString sqlcmd =
            "UPDATE guardian SET guardian_id = :guardian_id WHERE child_id = "
            ":child_id;";
    query->prepare(sqlcmd);
    query->bindValue(":child_id", id);
    query->bindValue(":guardian_id", guardian_id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::UserDB::check_guardian(int id) {
    QString sqlcmd =
            "SELECT COUNT(*) FROM user WHERE id = :id AND access & 2 = 2;";
    query->prepare(sqlcmd);
    query->bindValue(":id", id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::UserDB::max_userid() {
    QString sqlcmd = "SELECT MAX(id) FROM user;";
    if (query->exec(sqlcmd) == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::UserDB::fetch_cfg(int user_id, std::string key) {
    QString sqlcmd = "SELECT " + QString::fromStdString(key)
            + " FROM config WHERE user_id = :user_id;";
    query->prepare(sqlcmd);
    query->bindValue(":user_id", user_id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::UserDB::update_cfg(int user_id, std::string key, int val) {
    QString sqlcmd = "UPDATE config SET " + QString::fromStdString(key)
            + " = :val WHERE user_id = :user_id;";
    query->prepare(sqlcmd);
    query->bindValue(":user_id", user_id);
    query->bindValue(":val", val);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::UserDB::touch_cfg(int id) {
    QString sqlcmd =
        "INSERT INTO config VALUES (:user_id,0,1,0,2,3) ON CONFLICT DO "
        "NOTHING;";
    query->prepare(sqlcmd);
    query->bindValue(":user_id", id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}
