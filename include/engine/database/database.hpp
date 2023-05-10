#pragma once

#include <sqlite3.h>

#include <string>

class Database {
public:
    Database(std::string filename = "data.db");
    ~Database();

protected:
    sqlite3* db;
    sqlite3_stmt* statement;

    void selectTable(std::string table);
    void selectByKey(std::string table, std::string key);
    void selectByKey(std::string table, int key);
    bool step();
    void finalize();
    void execute(std::string sql);

    std::string toString(int column);
    int toInt(int col);
    float toFloat(int col);

    std::string table;

    std::string pkey;

    int rc;
};
