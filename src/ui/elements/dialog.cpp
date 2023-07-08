#include <ui/elements/dialog.hpp>

#include <engine/resources/palette.hpp>

#include <engine/util/text.hpp>

Dialog::Dialog(const sf::Font* font, const sf::Vector2f& w_size, const unsigned int c_size)
    : w_size { w_size }
    , font { font }
    , c_size { c_size }
{
    backdrop.setSize(w_size);
    backdrop.setFillColor(sf::Color(15, 15, 15, 125));

    const sf::Vector2f size(512.f, 512.f);
    sf::Vector2f pos((w_size.x / 2.f) - (size.x / 2.f), (w_size.y / 2.f) - (size.y / 2.f));
    frame.setPosition(pos);
    frame.setSize(size);
    frame.setFillColor(Palette::black);

    pos += sf::Vector2f(16.f, 16.f);
    text.setPosition(pos);
    text.setFont(*font);
    text.setFillColor(Palette::white);

    //activate();
}

Dialog::~Dialog()
{
    //deactivate();
}

void Dialog::addButton(std::string text, std::function<void()> target, Position pos, Target_Type type)
{
    buttons.push_back(std::make_pair(std::make_unique<Button>(text, *font, target, c_size), pos));
    Button* b = buttons.back().first.get();
    switch (type) {
        case CANCEL:
            cancel = b;
            break;
        case CONFIRM:
            confirm = b;
            break;
        default:
            break;
    }
}

void Dialog::setText(std::string tstr)
{
    text.setString(tstr);
    float width = frame.getSize().x - 32.f;
    wrapText(text, width);
}

void Dialog::setTextbox(std::string title, bool sanitized, std::string tstr)
{
    textbox = std::make_unique<Simple_Textbox>(title, sanitized);
    textbox->setFont(*font);

    textbox->setString(tstr);

    sf::Vector2f size = frame.getSize();
    size.x -= 32.f;
    size.y = 96.f;
    textbox->setSize(size);

    sf::Vector2f pos = text.getPosition();
    textbox->setPosition(pos);
    pos.y += textbox->getSize().y;
    pos.y += 16.f;
    text.setPosition(pos);
    textbox->activate();

    textbox->setOutline();
}

bool Dialog::update(const sf::Vector2i& mpos)
{
    if (textbox && textbox->update(mpos)) {
        moused = textbox.get();
    }
    else {
        for (auto& button : buttons) {
            if (button.first->update(mpos)) {
                moused = button.first.get();
                return (moused);
            }
        }
        moused = nullptr;
    }
    return moused;
}

bool Dialog::clickLeft()
{
    if (moused) {
        moused->clickLeft();
        return true;
    }

    return false;
}

bool Dialog::releaseLeft()
{
    if (moused) {
        moused->releaseLeft();
        return true;
    }

    return false;
}

bool Dialog::clickRight()
{
    if (moused && moused != textbox.get()) {
        moused->clickRight();
        return true;
    }

    return false;
}

bool Dialog::textEntered(const sf::Event& event)
{
    switch (event.text.unicode) {
        case UNICODE_ESCAPE:
            (*cancel)();
            return true;
        case UNICODE_RETURN:
            if (confirm->available()) {
                (*confirm)();
                return true;
            }
            return false;
        default:
            if (textbox) {
                textbox->textEntered(event);
                if (textbox->getString().length() > 0) {
                    confirm->setState(READY);
                }
                else {
                    confirm->setState(UNAVAILABLE);
                }
                return true;
            }
            return false;
    }
}

std::string Dialog::getString()
{
    std::string t {};
    if (textbox) {
        t = textbox->getString();
    }
    return t;
}

void Dialog::setCancel(std::function<void()> target, Position pos)
{
    addButton("confirm", target, pos, CANCEL);
    sf::Vector2f cpos = frame.getPosition() - frame.getOrigin();
    cpos.y += frame.getSize().y;
    cpos.y -= buttons.back().first->getSize().y;
    buttons.back().first->setPosition(cpos);
}

void Dialog::setConfirm(std::function<void()> target, Position pos)
{
    addButton("confirm", target, pos, CONFIRM);
    sf::Vector2f cpos = frame.getPosition() - frame.getOrigin();
    cpos += frame.getSize();
    cpos -= buttons.back().first->getSize();
    buttons.back().first->setPosition(cpos);
}

void Dialog::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(backdrop, states);
    target.draw(frame, states);
    if (textbox) {
        target.draw(*textbox, states);
    }
    target.draw(text, states);
    for (const auto& button : buttons) {
        target.draw(*button.first, states);
    }
}

