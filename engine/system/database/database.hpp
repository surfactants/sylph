#pragma once

#include <sqlite3.h>

#include <string>

class Database {
public:
    Database(std::string filename = "data.db");
    ~Database();

    std::string toString(int column);

protected:
    sqlite3* db;
    sqlite3_stmt* statement;

    void selectTable(std::string table);
    bool step();
    void finalize();
    void execute(std::string sql);

    std::string table;

    int rc;
};
