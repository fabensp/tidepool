#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>

#include "QString"
#include "QSqlDatabase"
#include "QSqlQuery"
#include "QSqlError"
#include "QVariant"
#include "QSqlRecord"

namespace db {

/**
 * @brief The Database class provides a base class for interacting with a database.
 */
class Database
{
public:
    /**
         * @brief Constructs a Database object with the specified database file.
         * @param file The database file name.
         */
    Database(std::string file);

    /**
         * @brief Destroys the Database object and closes the database connection.
         */
    ~Database();

    /**
         * @brief Moves the query to the next result.
         * @return True if there is a next result, false otherwise.
         */
    bool next();

    /**
         * @brief Moves the query to the last result.
         * @return True if there is a last result, false otherwise.
         */
    bool last();

    /**
         * @brief Moves the query to the first result.
         * @return True if there is a first result, false otherwise.
         */
    bool first();

    /**
         * @brief Retrieves the result of the executed query.
         * @return A pointer to the QSqlQuery object containing the result.
         */
    const QSqlQuery *result();

    /**
         * @brief Performs a test operation on the database connection.
         */
    void test();

protected:
    QSqlDatabase db;
    QSqlQuery *query;
};

}
#endif // DATABASE_H
