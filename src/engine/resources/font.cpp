#include <engine/resources/font.hpp>

std::string fontToString(Font f)
{
    return std::string(magic_enum::enum_name(f));
}

Font stringToFont(std::string s)
{
    return magic_enum::enum_cast<Font>(s).value_or(Font::MENU);
}
