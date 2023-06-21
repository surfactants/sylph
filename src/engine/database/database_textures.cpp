#include <engine/database/database_textures.hpp>

Database_Textures::Database_Textures()
{
    selectTable("TEXTURES");
}

void Database_Textures::read(std::map<std::string, sf::Texture>& textures)
{
    int row { 1 };
    while (step()) {
        std::string key = toString(0);
        Blob blob = toBlob(row++, "DATA");
        sf::Texture t;
        textures[key].loadFromMemory(blob.buffer.get(), blob.length);
    }
}
