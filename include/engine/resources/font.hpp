#pragma once

#include <SFML/Graphics/Font.hpp>

#include <magic_enum.hpp>

enum class Font {
    MENU,
    UI
};

std::string fontToString(Font f);

Font stringToFont(std::string s);
