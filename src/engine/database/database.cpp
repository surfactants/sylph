#include <engine/database/database.hpp>

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

bool Database::step()
{
    bool row = (sqlite3_step(statement) == SQLITE_ROW);
    if (!row) {
        finalize();
    }
    return row;
}

void Database::finalize()
{
    rc = sqlite3_finalize(statement);
}

void Database::execute(std::string sql)
{
    rc = sqlite3_exec(db, sql.c_str(), 0, 0, 0);
}

std::string Database::toString(int column)
{
    return reinterpret_cast<const char*>(sqlite3_column_text(statement, column++));
}
