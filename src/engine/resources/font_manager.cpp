#include <engine/resources/font_manager.hpp>

#include <engine/database/database_fonts.hpp>

//std::map<Font, sf::Font> Font_Manager::fonts = std::map<Font, sf::Font>();

Font_Manager* Font_Manager::instance = nullptr;

Font_Manager::Font_Manager()
{
    Database_Fonts db;
    db.read(fonts);
}

sf::Font* Font_Manager::get(Font f)
{
    if (instance == nullptr) {
        instance = new Font_Manager();
    }

    return &(instance->fonts[f]);
}
