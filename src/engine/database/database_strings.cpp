#include <engine/database/database_strings.hpp>

Database_Strings::Database_Strings()
{
    selectTable("STRINGS");
}

void Database_Strings::read(std::map<std::string, std::string>& strings, std::string language)
{
    // find column index
    int language_index { -1 };
    while (sqlite3_column_name(statement, ++language_index) != language);

    while (step()) {
        strings[toString(0)] = toString(language_index);
    }
}
