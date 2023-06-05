#include <iostream>
#include "database.h"

int main()
{
    db::Database* db = new db::Database("../../database.sqlite");

    db->test();

    delete db;
}
