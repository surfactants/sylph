#include <menu/elements/dialog.hpp>

#include <engine/resources/palette.hpp>

#include <engine/util/text.hpp>

Dialog::Dialog(const sf::Font& font, const sf::Vector2f w_size)
    : w_size { w_size }
    , font { font }
{
    cancel = Button("cancel", font, 32);
    confirm = Button("confirm", font, 32);

    backdrop.setSize(w_size);
    backdrop.setFillColor(sf::Color(15, 15, 15, 125));

    const sf::Vector2f size(512.f, 512.f);
    sf::Vector2f pos((w_size.x / 2.f) - (size.x / 2.f), (w_size.y / 2.f) - (size.y / 2.f));
    frame.setPosition(pos);
    frame.setSize(size);
    frame.setFillColor(Palette::black);

    pos += sf::Vector2f(16.f, 16.f);
    text.setPosition(pos);
    text.setFont(font);
    text.setFillColor(Palette::white);

    pos -= sf::Vector2f(16.f, 16.f);
    pos.y += size.y;
    cancel.setPosition(pos);

    pos.x += size.x;
    confirm.setPosition(pos);

    //activate();
}

Dialog::~Dialog()
{
    //deactivate();
}

void Dialog::setCancel(std::function<void()> target)
{
    cancel.target = target;
}

void Dialog::setConfirm(std::function<void()> target)
{
    confirm.target = target;
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
    textbox->setFont(font);

    textbox->setString(tstr);

    sf::Vector2f size = frame.getSize();
    size.x -= 32.f;
    size.y = 96.f;
    textbox->setSize(size);

    sf::Vector2f pos = text.getPosition();
    textbox->setPosition(pos);
    pos.y += textbox->totalSize().y;
    pos.y += 16.f;
    text.setPosition(pos);
    textbox->activate();

    textbox->setOutline();
}

bool Dialog::update(const sf::Vector2i& mpos)
{
    if (cancel.update(mpos)) {
        moused = &cancel;
    }
    else if (confirm.update(mpos)) {
        moused = &confirm;
    }
    else if (textbox && textbox->update(mpos)) {
        moused = textbox.get();
    }
    else {
        moused = nullptr;
    }
    return (moused);
}

void Dialog::clickLeft()
{
    if (moused) {
        moused->clickLeft();
    }
}

void Dialog::releaseLeft()
{
    if (moused) {
        moused->releaseLeft();
    }
}

void Dialog::clickRight()
{
    if (moused && moused != textbox.get()) {
        moused->clickRight();
    }
}

void Dialog::textEntered(const sf::Event& event)
{
    switch (event.text.unicode) {
        case UNICODE_ESCAPE:
            cancel();
            break;
        case UNICODE_RETURN:
            if (confirm.available()) {
                confirm();
            }
            break;
        default:
            if (textbox) {
                textbox->textEntered(event);
                if (textbox->getString().length() > 0) {
                    confirm.setState(READY);
                }
                else {
                    confirm.setState(UNAVAILABLE);
                }
            }
            break;
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

void Dialog::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(backdrop, states);
    target.draw(frame, states);
    if (textbox) {
        target.draw(*textbox, states);
    }
    target.draw(text, states);
    target.draw(cancel, states);
    target.draw(confirm, states);
}
