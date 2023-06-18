#include <engine/database/database_settings_general.hpp>

#include <iostream>

Database_Settings_General::Database_Settings_General()
{
    selectTable("GENERAL_SETTINGS");
}

std::string Database_Settings_General::activeLanguage()
{
    // for simplicity in the localizer

    // step once, as active settings are the first record.
    step();

    // find the column, read it
    int i { -1 };
    std::string target { "LANGUAGE" };
    while (sqlite3_column_name(statement, ++i) != target);
        // ha ha this will cause an infinite loop if the table name doesn't exist
    std::cout << i << '\n';
    std::string lang = toString(i);

    // step() normally finalizes, but it did not reach the end
    finalize();

    return lang;
}
