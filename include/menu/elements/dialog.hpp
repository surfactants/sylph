#pragma once

#include "menu_element.hpp"

#include "button.hpp"
#include "simple_textbox.hpp"

class Dialog : public Menu_Element {
public:
    Dialog(const sf::Font& font, const sf::Vector2f w_size);
    ~Dialog();

    void setCancel(std::function<void()> target);
    void setConfirm(std::function<void()> target);

    virtual bool update(const sf::Vector2i& mpos) override;
    virtual void clickLeft() override;
    virtual void releaseLeft() override;
    virtual void clickRight() override;
    virtual void textEntered(const sf::Event& event);

    void setText(std::string tstr);
    void setTextbox(std::string title, bool sanitized, std::string tstr = "");

    std::string getString();

private:
    sf::RectangleShape backdrop;
    sf::Text text;
    Button cancel;
    Button confirm;
    const sf::Vector2f w_size;

    std::unique_ptr<Simple_Textbox> textbox { nullptr };
    const sf::Font& font;

    Menu_Element* moused;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
