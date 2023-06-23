#pragma once

#include "element.hpp"

#include "button.hpp"
#include "simple_textbox.hpp"

class Dialog : public Element {
public:
    Dialog(const sf::Font* font, const sf::Vector2f& w_size, const unsigned int c_size = 24);
    ~Dialog();

    enum Position {
        TOP,
        LEFT,
        BOTTOM,
        RIGHT
    };

    enum Target_Type {
        CANCEL,
        CONFIRM,
        NULL_TARGET
    };

    void setCancel(std::function<void()> target, Position pos = BOTTOM);
    void setConfirm(std::function<void()> target, Position pos = BOTTOM);

    virtual bool update(const sf::Vector2i& mpos) override;

    virtual bool clickLeft() override;
    virtual bool releaseLeft() override;
    virtual bool clickRight() override;
    virtual bool textEntered(const sf::Event& event);

    void setText(std::string tstr);
    void setTextbox(std::string title, bool sanitized, std::string tstr = "");

    std::string getString();

    void addButton(std::string text, std::function<void()> target, Position pos, Target_Type type = NULL_TARGET);

protected:
    sf::RectangleShape backdrop;
    sf::Text text;
    Button* confirm;
    Button* cancel;
/*
    Button cancel;
    Button confirm;
*/
    const sf::Vector2f w_size;

    std::vector<std::pair<std::unique_ptr<Button>, Position>> buttons;

    std::unique_ptr<Simple_Textbox> textbox { nullptr };
    const sf::Font* font;

    Element* moused;

    unsigned int c_size;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

