#include "profiledb.h"

db::ProfileDB::ProfileDB(std::string file): Database(file)
{

}

void db::ProfileDB::fetch_profile_id(int user_id) {
    QString sqlcmd =
        "SELECT avatar_id, display_name, bio, fish_day, theme "
        "FROM profile WHERE user_id = :user_id;";
    query->prepare(sqlcmd);
    query->bindValue(":user_id", user_id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ProfileDB::fetch_profile_display_name(std::string display_name) {
    QString sqlcmd =
        "SELECT user_id, avatar_id, bio, fish_day, theme "
        "FROM profile WHERE display_name = :display_name;";
    query->prepare(sqlcmd);
    query->bindValue(":display_name", QString::fromStdString(display_name));
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ProfileDB::fetch_links(int user_id) {
    QString sqlcmd = "SELECT label, link FROM link WHERE user_id = :user_id;";
    query->prepare(sqlcmd);
    query->bindValue(":user_id", user_id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ProfileDB::fetch_pals(int user_id) {
    QString sqlcmd =
        "SELECT id, avatar_id, name, species, birthday, bio "
        "FROM pal WHERE user_id = :user_id;";
    query->prepare(sqlcmd);
    query->bindValue(":user_id", user_id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ProfileDB::fetch_pal(int id) {
    QString sqlcmd = "SELECT user_id, avatar_id, name, species, "
                     "birthday, bio FROM pal WHERE id = :id;";
    query->prepare(sqlcmd);
    query->bindValue(":id", id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ProfileDB::fetch_shoal_tag(int member_id) {
    QString sqlcmd =
            "SELECT shoal_tag FROM shoal_membership "
            "WHERE member_id = :member_id;";
    query->prepare(sqlcmd);
    query->bindValue(":member_id", member_id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

//Should get the to_user_id's
void db::ProfileDB::fetch_reef(int from_user_id) {
    QString sqlcmd = "SELECT to_user_id FROM reef "
                     "WHERE from_user_id = :from_user_id;";
    query->prepare(sqlcmd);
    query->bindValue(":from_user_id", from_user_id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ProfileDB::edit_profile(int id, int avatar_id,
                                 std::string display_name, std::string bio,
                                 std::string fish_day, int theme) {
    QString sqlcmd =
        "UPDATE profile SET avatar_id = :aid, display_name = :dn, bio = :bio, "
        "fish_day = :fd, theme = :t WHERE user_id = :uid;";
    query->prepare(sqlcmd);
    query->bindValue(":uid", id);
    query->bindValue(":aid", avatar_id);
    query->bindValue(":dn", QString::fromStdString(display_name));
    query->bindValue(":bio", QString::fromStdString(bio));
    query->bindValue(":fd", QString::fromStdString(fish_day));
    query->bindValue(":t", theme);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ProfileDB::edit_display_name(int user_id, std::string display_name) {
    QString sqlcmd = "UPDATE profile SET display_name = :display_name WHERE user_id = :user_id;";
    query->prepare(sqlcmd);
    query->bindValue(":display_name", QString::fromStdString(display_name));
    query->bindValue(":user_id", user_id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ProfileDB::edit_avatarId(int user_id, int avatar_id) {
    QString sqlcmd = "UPDATE profile SET avatar_id = :avatar_id WHERE user_id = :user_id;";
    query->prepare(sqlcmd);
    query->bindValue(":avatar_id", avatar_id);
    query->bindValue(":user_id", user_id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ProfileDB::edit_bio(int user_id, std::string bio) {
    QString sqlcmd = "UPDATE profile SET bio = :bio WHERE user_id = :user_id;";
    query->prepare(sqlcmd);
    query->bindValue(":bio", QString::fromStdString(bio));
    query->bindValue(":user_id", user_id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ProfileDB::edit_fishDay(int user_id, std::string fish_day) {
    QString sqlcmd = "UPDATE profile SET fish_day = :fish_day WHERE user_id = :user_id;";
    query->prepare(sqlcmd);
    query->bindValue(":fish_day", QString::fromStdString(fish_day));
    query->bindValue(":user_id", user_id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ProfileDB::edit_theme(int user_id, int theme) {
    QString sqlcmd = "UPDATE profile SET theme = :theme WHERE user_id = :user_id;";
    query->prepare(sqlcmd);
    query->bindValue(":theme", theme);
    query->bindValue(":user_id", user_id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ProfileDB::insert_shoal_membership(int member_id, std::string shoal_tag) {
    QString sqlcmd = "INSERT INTO shoal_membership (member_id, shoal_tag) "
                     "VALUES (:member_id, :shoal_tag);";
    query->prepare(sqlcmd);
    query->bindValue(":member_id", member_id);
    query->bindValue(":shoal_tag", QString::fromStdString(shoal_tag));
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ProfileDB::remove_shoal_membership(int member_id, std::string shoal_tag) {
    QString sqlcmd = "DELETE FROM shoal_membership WHERE member_id = :member_id "
                     "AND shoal_tag = :shoal_tag;";
    query->prepare(sqlcmd);
    query->bindValue(":member_id", member_id);
    query->bindValue(":shoal_tag", QString::fromStdString(shoal_tag));
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ProfileDB::insert_link(int user_id, std::string label,
                                std::string link) {
    QString sqlcmd =
        "INSERT INTO link (user_id, label, link) VALUES (:id, :la, :li) "
        "ON CONFLICT DO NOTHING;";
    query->prepare(sqlcmd);
    query->bindValue(":id", user_id);
    query->bindValue(":la", QString::fromStdString(label));
    query->bindValue(":li", QString::fromStdString(link));
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ProfileDB::remove_link(int user_id, std::string tag,
                                std::string link) {
    QString sqlcmd =
        "DELETE FROM link WHERE user_id = :id AND label = :la AND link = :li;";
    query->prepare(sqlcmd);
    query->bindValue(":id", user_id);
    query->bindValue(":la", QString::fromStdString(tag));
    query->bindValue(":li", QString::fromStdString(link));
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ProfileDB::create_reef(int from_user_id, int to_user_id) {
    QString sqlcmd = "INSERT INTO reef (from_user_id, to_user_id) "
                     "VALUES (:from_user_id, :to_user_id);";
    query->prepare(sqlcmd);
    query->bindValue(":from_user_id", from_user_id);
    query->bindValue(":to_user_id", to_user_id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ProfileDB::remove_reef(int from_user_id, int to_user_id) {
    QString sqlcmd =
        "DELETE FROM reef WHERE from_user_id = :from_user_id AND to_user_id = :to_user_id;";
    query->prepare(sqlcmd);
    query->bindValue(":from_user_id", from_user_id);
    query->bindValue(":to_user_id", to_user_id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ProfileDB::add_pal(int user_id, int id, int avatar_id, std::string name, std::string species, std::string birthday, std::string bio) {
    QString sqlcmd = "INSERT INTO pal (user_id, id, avatar_id, name, species, birthday, bio) "
                     "VALUES (:user_id, :id, :avatar_id, :name, :species, :birthday, :bio);";
    query->prepare(sqlcmd);
    query->bindValue(":user_id", user_id);
    query->bindValue(":id", id);
    query->bindValue(":avatar_id", avatar_id);
    query->bindValue(":name", QString::fromStdString(name));
    query->bindValue(":species", QString::fromStdString(species));
    query->bindValue(":birthday", QString::fromStdString(birthday));
    query->bindValue(":bio", QString::fromStdString(bio));
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ProfileDB::remove_pal(int id) {
    QString sqlcmd =
        "DELETE FROM pal WHERE id = :id;";
    query->prepare(sqlcmd);
    query->bindValue(":id", id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ProfileDB::edit_pal_avatar_id(int id, int avatar_id) {
    QString sqlcmd = "UPDATE pal SET avatar_id = :avatar_id WHERE id = :id;";
    query->prepare(sqlcmd);
    query->bindValue(":avatar_id", avatar_id);
    query->bindValue(":id", id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ProfileDB::edit_pal_name(int id, std::string name) {
    QString sqlcmd = "UPDATE pal SET name = :name WHERE id = :id;";
    query->prepare(sqlcmd);
    query->bindValue(":name", QString::fromStdString(name));
    query->bindValue(":id", id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ProfileDB::edit_pal_species(int id, std::string species) {
    QString sqlcmd = "UPDATE pal SET species = :species WHERE id = :id;";
    query->prepare(sqlcmd);
    query->bindValue(":species", QString::fromStdString(species));
    query->bindValue(":id", id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ProfileDB::edit_pal_birthday(int id, std::string birthday) {
    QString sqlcmd = "UPDATE pal SET birthday = :birthday WHERE id = :id;";
    query->prepare(sqlcmd);
    query->bindValue(":birthday", QString::fromStdString(birthday));
    query->bindValue(":id", id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ProfileDB::edit_pal_bio(int id, std::string bio) {
    QString sqlcmd = "UPDATE pal SET bio = :bio WHERE id = :id;";
    query->prepare(sqlcmd);
    query->bindValue(":bio", QString::fromStdString(bio));
    query->bindValue(":id", id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ProfileDB::insert_profile_avatar(int id, QByteArray content) {
    QString sqlcmd = "INSERT INTO avatar (id, content) VALUES (:id, :content);";
    query->prepare(sqlcmd);
    query->bindValue(":id", id);
    query->bindValue(":content", content);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ProfileDB::fetch_profile_avatar(int id) {
    QString sqlcmd = "SELECT content FROM avatar WHERE id = :id;";
    query->prepare(sqlcmd);
    query->bindValue(":id", id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ProfileDB::max_pal_id() {
    QString sqlcmd = "SELECT MAX(id) FROM pal;";
    if (query->exec(sqlcmd) == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ProfileDB::fish_time(int id) {
    QString sqlcmd =
        "SELECT julianday('now') - julianday(fish_day) FROM profile WHERE "
        "user_id = :id;";
    query->prepare(sqlcmd);
    query->bindValue(":id", id);
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void db::ProfileDB::create_profile(int id, std::string fishday) {
    QString sqlcmd =
        "INSERT INTO profile SELECT :id, 0, username, '', :fd, 0 FROM user "
        "WHERE id = :id;";
    query->prepare(sqlcmd);
    query->bindValue(":id", id);
    query->bindValue(":fd", QString::fromStdString(fishday));
    if (query->exec() == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}
