#include <ui/elements/simple_textbox.hpp>

#include <engine/resources/palette.hpp>

Simple_Textbox::Simple_Textbox(std::string title_text, bool sanitized)
{
    //set text defaults
    max_length = 32;
    text_size = 32;

    title.setFillColor(Palette::white);
    title.setString(title_text);
    title.setCharacterSize(48);

    text.setFillColor(Palette::white);
    text.setCharacterSize(text_size);

    cursor.setFillColor(sf::Color::Transparent);
    cursor.setCharacterSize(text_size);
    cursor.setString("|");
    placeCursor();

    //set box defaults
    frame.setSize(sf::Vector2f(256.f, 96.f));
    frame.setPosition(sf::Vector2f(160, 440));
    frame.setFillColor(Palette::black);

    state = READY;
    base_state = READY;

    if (sanitized) {
        disallowed = "/:*?<>|\"\\";
    }
}

void Simple_Textbox::setFont(const sf::Font& font)
{
    text.setFont(font);
    cursor.setFont(font);
    title.setFont(font);
}

void Simple_Textbox::setMaxLength(unsigned int max_length)
{
    this->max_length = max_length;
}

unsigned int Simple_Textbox::getMaxLength()
{
    return max_length;
}

bool Simple_Textbox::textEntered(const sf::Event& event)
{
    if (event.key.code == sf::Keyboard::Left) {
        return true;
    }
    else if (event.type == sf::Event::TextEntered && event.text.unicode < 128) {
        switch (event.text.unicode) {
            case UNICODE_BACKSPACE:
                backspace();
                break;
            case UNICODE_CTRL_BACKSPACE:
                ctrlBackspace();
                break;
            case UNICODE_RETURN:
                // confirm
                deactivate();
                break;
            case UNICODE_ESCAPE:
                // confirm
                deactivate();
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
        return true;
    }
    return false;
}

void Simple_Textbox::setOutline()
{
    frame.setOutlineColor(Palette::white);
    frame.setOutlineThickness(1.f);
}

void Simple_Textbox::setString(std::string tstr)
{
    if (tstr.length() > max_length) {
        tstr = tstr.substr(0, max_length);
    }

    text.setString(tstr);

    index = tstr.length();
    placeCursor();
}

bool Simple_Textbox::keyPressed(sf::Keyboard::Key key)
{
    switch (key) {
        case sf::Keyboard::Left:
            scrollLeft();
            return true;
        case sf::Keyboard::Right:
            scrollRight();
            return true;
        default:
            return false;
    }
}

void Simple_Textbox::append(sf::String addition)
{
    for (auto& c : addition) {
        if (disallowed.find(c) != std::string::npos) {
            return;
        }
    }
    size_t n = addition.getSize();
    sf::String string = text.getString();

    if (n > 0 && string.getSize() + n < max_length) {
        string = string.substring(0, index) + addition + string.substring(index);
        text.setString(string);
        index += n;
        placeCursor();
    }
    // reset cursor blink
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
    text.setString("");
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

bool Simple_Textbox::empty()
{
    return (text.getString().getSize() == 0);
}

std::string Simple_Textbox::getString()
{
    return text.getString();
}

void Simple_Textbox::placeCursor()
{
    sf::Vector2f cpos(0.f, 0.f);
    const unsigned int textSize = text.getString().getSize();
    if (textSize == 0) {
        cpos = text.getPosition();
    }
    else if (textSize > index) {
        cpos = text.findCharacterPos(index);
        cpos.x -= text.getFont()->getGlyph(text.getString()[index], text.getCharacterSize(), false, 0).bounds.left;
        cpos.x -= text.getLocalBounds().left;
        cpos.x -= text.getLetterSpacing();
    }
    else if (index == textSize) {
        cpos = text.findCharacterPos(index - 1);
        cpos.x += text.getFont()->getGlyph(text.getString()[index - 1], text.getCharacterSize(), false, 0).bounds.width;
    }
    else {
        cpos = text.getPosition();
    }

    cursor.setPosition(cpos);
}

void Simple_Textbox::setSize(sf::Vector2f size)
{
    frame.setSize(size);
    text_offset.y = (size.y - text.getCharacterSize()) / 2.f;
    setPosition(title.getPosition());
    placeCursor();
}

sf::Vector2f Simple_Textbox::getSize()
{
    return frame.getSize();
}

sf::Vector2f Simple_Textbox::totalSize()
{
    sf::Vector2f size = frame.getSize();
    size.y += (frame.getPosition().y - title.getPosition().y);
    return size;
}

void Simple_Textbox::setPosition(sf::Vector2f pos)
{
    title.setPosition(pos);
    pos.y += title.getLocalBounds().top + title.getLocalBounds().height + 16.f;
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
    // cursor blink
    bool cnt = contains(mpos);
    if (cnt) {
        state = HIGHLIGHTED;
    }
    else {
        state = READY;
    }
    return cnt;
}

bool Simple_Textbox::clickLeft()
{
    switch (state) {
        case HIGHLIGHTED:
            activate();
            // reset cursor blink
            return true;
        default:
            deactivate();
            return false;
    }
}

void Simple_Textbox::activate()
{
    Element::activate();
    cursor.setFillColor(Palette::white);
    placeCursor();
}

void Simple_Textbox::deactivate()
{
    Element::deactivate();
    cursor.setFillColor(sf::Color::Transparent);
}

bool Simple_Textbox::releaseLeft()
{
    return (highlighted());
}

bool Simple_Textbox::releaseRight()
{
    deactivate();
    return true;
}

void Simple_Textbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(title, states);
    target.draw(frame, states);
    target.draw(text, states);
    target.draw(cursor, states);
}
