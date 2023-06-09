#include <engine/database/database_fonts.hpp>

std::vector<char*> Database_Fonts::buffers;

void Database_Fonts::read(std::map<Font, sf::Font>& fonts)
{
    using magic_enum::enum_cast;

    selectTable("FONTS");

    int row { 0 };

    std::cout << "\n\n";

    while (step()) {
        Font font_type = stringToFont(toString(0));
        sqlite3_blob* blob;
        rc = sqlite3_blob_open(db, "main", "FONTS", "DATA", ++row, 0, &blob);
        int bsize = sqlite3_blob_bytes(blob);
        char* buffer = new char[bsize];
        rc = sqlite3_blob_read(blob, buffer, bsize, 0);
        fonts[font_type].loadFromMemory(buffer, bsize);
        sqlite3_blob_close(blob);
        buffers.push_back(buffer);
    }
}
