#pragma once

#include <sqlite3.h>

#include <memory>
#include <string>

/// DATABASE ///
/// \brief base class for accessing sqlite databases.
/// simple extension:
/// - by default, it opens "data.db".
/// to avoid this, pass a string to the base constructor in the derived initializer list.
/// - call selectTable(table_name)
/// - while(step()) loop
/// - do the loop even for tables with only one row by design.
/// this is because step() also calls finalize() when there are no more rows available.

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

    struct Blob {
        Blob() = default;
        Blob(int length)
            : length { length }
        {
            buffer = std::shared_ptr<char[]>(new char[length]);
        }

        std::shared_ptr<char[]> buffer;
        int length;
    };

    /// blob ///
    /// \brief reads a blob from the selected table.
    Blob toBlob(int row, const std::string cname = "DATA");

    std::string table;

    std::string pkey;

    int rc;
};
