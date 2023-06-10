#include <engine/database/database.hpp>

#include <iostream>

// #include <format>
// someday...

Database::Database(std::string filename)
{
    if (filename.find(".db") == std::string::npos) {
        filename += ".db";
    }
    rc = sqlite3_open(filename.c_str(), &db);
}

Database::~Database()
{
    rc = sqlite3_close(db);
}

void Database::selectTable(std::string table)
{
    this->table = table;
    std::string sql = "SELECT * FROM '" + table + "';";
    sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &statement, NULL);
}

void Database::selectByKey(std::string table, std::string key)
{
    this->table = table;
    std::string sql = "SELECT * FROM " + table + " WHERE " + pkey + " = '" + key + "';";
    rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &statement, NULL);
    if (rc != SQLITE_OK) {
        std::cout << "----- SQLITE QUERY FAILED -----" << '\n';
        std::cout << sql << '\n';
        std::cout << rc << ": " << sqlite3_errmsg(db) << '\n';
    }
}

void Database::selectByKey(std::string table, int key)
{
    this->table = table;
    std::string sql = "SELECT * FROM pragma_table_info('" + table + "') WHERE " + pkey + " = " + std::to_string(key) + ";";
    rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &statement, NULL);
    if (rc != SQLITE_OK) {
        std::cout << "----- SQLITE QUERY FAILED -----" << '\n';
        std::cout << sql << '\n';
        std::cout << rc << ": " << sqlite3_errmsg(db) << '\n';
    }
}

bool Database::step()
{
    rc = sqlite3_step(statement);
    bool row = (rc == SQLITE_ROW);
    if (!row) {
        if (rc != SQLITE_OK && rc != SQLITE_DONE) {
            std::cout << "----- SQLITE STEP FAILED -----" << '\n';
            std::cout << rc << ": " << sqlite3_errmsg(db) << '\n';
        }
        else {
            finalize();
        }
    }
    return row;
}

void Database::finalize()
{
    rc = sqlite3_finalize(statement);
    if (rc != SQLITE_OK) {
        std::cout << "----- SQLITE FINALIZE FAILED -----" << '\n';
        std::cout << rc << ": " << sqlite3_errmsg(db) << '\n';
    }
}

void Database::execute(std::string sql)
{
    rc = sqlite3_exec(db, sql.c_str(), 0, 0, 0);
    if (rc != SQLITE_OK) {
        std::cout << "----- SQLITE QUERY FAILED -----" << '\n';
        std::cout << sql << '\n';
        std::cout << rc << ": " << sqlite3_errmsg(db) << '\n';
    }
}

std::string Database::toString(int column)
{
    return reinterpret_cast<const char*>(sqlite3_column_text(statement, column));
}

int Database::toInt(int column)
{
    return sqlite3_column_int(statement, column);
}

float Database::toFloat(int column)
{
    return sqlite3_column_double(statement, column);
}

Database::Blob Database::toBlob(int row, const std::string cname)
{
    sqlite3_blob* sql_blob;
    rc = sqlite3_blob_open(db, "main", table.c_str(), cname.c_str(), row, 0, &sql_blob);
    Blob blob(sqlite3_blob_bytes(sql_blob));
    sqlite3_blob_read(sql_blob, blob.buffer.get(), blob.length, 0);
    sqlite3_blob_close(sql_blob);
    return blob;
}
