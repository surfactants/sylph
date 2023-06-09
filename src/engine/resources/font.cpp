#include <engine/resources/font.hpp>

std::string fontToString(Font f)
{
    return std::string(magic_enum::enum_name(f));
}

Font stringToFont(std::string s)
{
    return magic_enum::enum_cast<Font>(s).value_or(Font::MENU);
}

/*
void Database::getFonts(std::map<Font, sf::Font>& f)
{
    open();

    std::string sql = "SELECT * FROM 'FONTS';";

    sqlite3_stmt* statement;

    rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &statement, NULL);

    int row = 0;

    while ((rc = sqlite3_step(statement)) == SQLITE_ROW) {
        int column = 0;
        std::string name = reinterpret_cast<const char*>(sqlite3_column_text(statement, column));

        sqlite3_blob* blob;

        rc = sqlite3_blob_open(db, "main", "FONTS", "DATA", ++row, 0, &blob);
        errorCheck(std::string("opening font blob " + name));

        int bsize = sqlite3_blob_bytes(blob);
        font_buffers.push_back(new char[bsize]);

        rc = sqlite3_blob_read(blob, font_buffers.back(), bsize, 0);
        errorCheck(std::string("\treading font blob " + name));

        f[stringToFont(name)].loadFromMemory(font_buffers.back(), bsize);

        rc = sqlite3_blob_close(blob);
    }

    sqlite3_finalize(statement);

    close();
}
*/
