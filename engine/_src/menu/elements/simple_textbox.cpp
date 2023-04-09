#include <menu/elements/simple_textbox.hpp>

#include <resources/palette.hpp>

// define certain constants for reading text
#define UNICODE_SELECT_ALL 1
#define UNICODE_COPY 3
#define UNICODE_BACKSPACE 8
#define UNICODE_RETURN 13
#define UNICODE_PASTE 22
#define UNICODE_CUT 24
#define UNICODE_ESCAPE 27
#define UNICODE_CTRL_BACKSPACE 127

Simple_Textbox::Simple_Textbox()
{

    //set text defaults
    max_length = 32;
    text_size = 32;

    text.setFillColor(Palette::white);
    text.setCharacterSize(text_size);

    cursor.setFillColor(sf::Color(250,250,250,255));
    cursor.setCharacterSize(text_size);
    cursor.setString("|");
    placeCursor();

    //set box defaults
    frame.setSize(sf::Vector2f(256.f, 96.f));
    frame.setPosition(sf::Vector2f(160,440));
    frame.setFillColor(Palette::black);
}

void Simple_Textbox::setFont(sf::Font& font)
{
    text.setFont(font);
    cursor.setFont(font);
}

void Simple_Textbox::setMaxLength(unsigned int newMax)
{
    max_length = newMax;
}

unsigned int Simple_Textbox::getMaxLength()
{
    return max_length;
}

void Simple_Textbox::readText(const sf::Event& event)
{
    if (event.key.code == sf::Keyboard::Left) {
    }
    if(event.type == sf::Event::TextEntered && event.text.unicode < 128) {
        switch (event.text.unicode) {
            case UNICODE_BACKSPACE:
                backspace();
                break;
            case UNICODE_CTRL_BACKSPACE:
                ctrlBackspace();
                break;
            case UNICODE_RETURN:
                // confirm
                clearActive();
                break;
            case UNICODE_ESCAPE:
                // confirm
                clearActive();
                break;
            case UNICODE_CUT:
                break;
            case UNICODE_COPY:
                break;
            case UNICODE_PASTE:
                break;
            default:
                if (event.text.unicode > 31) {
                    append(sf::String(event.text.unicode));
                }
                break;
        }
    }
}

void Simple_Textbox::append(sf::String addition)
{
    size_t n = addition.getSize();
    sf::String string = text.getString();

    if (n > 0 && string.getSize() + n < max_length) {
        string = string.substring(0, index) + addition + string.substring(index);
        text.setString(string);
        index += n;
        placeCursor();
    }
}

void Simple_Textbox::backspace()
{
    sf::String string = text.getString();

    if (string.getSize() > 0) {
        string.erase(index - 1);
        text.setString(string);
        index--;
        placeCursor();
    }
}

void Simple_Textbox::ctrlBackspace()
{
    sf::String string = text.getString();
    bool erasing = true;
    while (erasing) {
        if (string.getSize() == 0) {
            break;
        }

        if (index > 0) {
            index--;
            erasing = (string[index] != ' ');
        }
        else {
            erasing = false;
        }

        string.erase(index);
    }

    text.setString(string);
    placeCursor();
}

void Simple_Textbox::clear()
{
    text.setString("");;
    index = 0;
    placeCursor();
}

void Simple_Textbox::scrollLeft()
{
    if (index > 0) {
        index--;
        placeCursor();
    }
}

void Simple_Textbox::scrollRight()
{
    if (index < text.getString().getSize()) {
        index++;
        placeCursor();
    }
}

std::string Simple_Textbox::getString()
{
    return text.getString();
}

void Simple_Textbox::placeCursor()
{
    sf::Vector2f cpos(0.f, 0.f);
    const unsigned int textSize = text.getString().getSize();
    if(textSize == 0) {
        cpos = text.getPosition();
    }
    else if(textSize > index) {
        cpos = text.findCharacterPos(index);
        cpos.x -= text.getFont()->getGlyph(text.getString()[index], text.getCharacterSize(), false, 0).bounds.left;
        cpos.x -= text.getLocalBounds().left;
        cpos.x -= text.getLetterSpacing();
    }
    else if(index == textSize) {
        cpos = text.findCharacterPos(index - 1);
        cpos.x += text.getFont()->getGlyph(text.getString()[index - 1], text.getCharacterSize(), false, 0).bounds.width;
    }
    else{
        cpos = text.getPosition();
    }

    cursor.setPosition(cpos);
}

void Simple_Textbox::setSize(sf::Vector2f size)
{
    frame.setSize(size);
}

sf::Vector2f Simple_Textbox::getSize()
{
    return frame.getSize();
}

void Simple_Textbox::setPosition(sf::Vector2f pos)
{
    frame.setPosition(pos);
    text.setPosition(pos + text_offset);
}

sf::Vector2f Simple_Textbox::getPosition()
{
    return frame.getPosition();
}

void Simple_Textbox::setTextSize(const unsigned int size)
{
    text_size = size;
    text.setCharacterSize(size);
    text_offset.y = (frame.getSize().y - text_size) / 2.f;
    setPosition(frame.getPosition());
    placeCursor();
}

bool Simple_Textbox::update(const sf::Vector2i& mpos)
{
    if (active()) {
        // cursor blink
    }
    return contains(mpos);
}

void Simple_Textbox::clickLeft()
{
    setActive(this);
    setState(ACTIVE);
    placeCursor();
}

void Simple_Textbox::releaseLeft()
{}

void Simple_Textbox::releaseRight()
{
    clearActive();
}

void Simple_Textbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(frame, states);
    target.draw(text, states);
    if (active()) {
        target.draw(cursor, states);
    }
}

