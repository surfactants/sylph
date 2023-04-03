#include <system/database/database.hpp>

Database::Database(std::string filename)
{
    if (filename.find(".db") == std::string::npos) {
        filename += ".db";
    }
    sqlite3_open(filename.c_str(), &db);
}

Database::~Database()
{
    sqlite3_close(db);
}

void Database::selectTable(std::string table)
{
    std::string sql = "SELECT * FROM '" + table + "';";
    sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &statement, NULL);
}

bool Database::step()
{
    bool row = (sqlite3_step(statement) == SQLITE_ROW);
    if (!row) {
        sqlite3_finalize(statement);
    }
    return row;
}

std::string Database::toString(int column)
{
    return reinterpret_cast<const char*>(sqlite3_column_text(statement, column++));
}
