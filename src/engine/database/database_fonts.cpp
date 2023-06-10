#include <engine/database/database_fonts.hpp>

std::vector<std::shared_ptr<char[]>> Database_Fonts::buffers;

void Database_Fonts::read(std::map<Font, sf::Font>& fonts)
{
    using magic_enum::enum_cast;

    selectTable("FONTS");

    int row { 1 }; // sqlite rows are 1-indexed

    while (step()) {
        Font font_type = stringToFont(toString(0));
        Blob blob = toBlob(row++);
        fonts[font_type].loadFromMemory(blob.buffer.get(), blob.length);
        buffers.push_back(blob.buffer);
    }
}
