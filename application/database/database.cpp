#include "database.h"

// Adapted from Lab 8

db::Database::Database(std::string file)
{
    QString path(QString::fromStdString(file));
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    // check db opened
    if (!db.open()) {

        std::cerr << "Error: connection with database fail" << std::endl;
        exit(1);
    } else {
        std::cout << "Database: connection ok" << std::endl;
    }

    query = new QSqlQuery(db);

}

db::Database::~Database() {
    db.close();
    delete query;
}

/***
 * returns true or false if there is another row available
 */
bool db::Database::next() {
    return query->next();
}

/***
 * returns true or false if the query is at the last row
 */
bool db::Database::last() {
    return query->last();
}

/***
 * returns true or false if the query is at the first row
 */
bool db::Database::first() {
    return query->first();
}

/***
 * Provides access to the dynamically allocated query object.
 * If it does not exist, returns null.
 */
const QSqlQuery *db::Database::result() {

    if (query) {
        return query;
    } else {
        return nullptr;
    }
}

void db::Database::test() {
    query->exec(
        "INSERT INTO user(id, username, email, password, access) VALUES "
        "(10000, 'testington', 'tester@example.com', 'password', 2);");
    query->exec("SELECT username FROM user WHERE id = 10000;");
    while (next()) {
        qDebug() << query->value(0);
    }
    qDebug() << "-";
    query->exec("UPDATE user SET username = 'testerson' WHERE id = 10000;");
    query->exec("SELECT username FROM user WHERE id = 10000;");
    while (next()) {
        qDebug() << query->value(0);
    }
    qDebug() << "-";
    query->exec("DELETE FROM user WHERE username = 'testerson';");
    query->exec("SELECT username FROM user WHERE id = 10000;");
    while (next()) {
        qDebug() << query->value(0);
    }
}
