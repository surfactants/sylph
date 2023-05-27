#pragma once

#include <SFML/Graphics.hpp>

#include <tuple>
#include <vector>

#include <engine/resources/palette.hpp>
#include <engine/util/text.hpp>

#include "menu_element.hpp"
#include "button.hpp"
#include "scrollable.hpp"

template <typename T>
class Toggle_Scroller : public Menu_Element, public Scrollable {
public:
    Toggle_Scroller(const sf::Font& font)
        : font { font }
    {
        setState(READY);
        scrollbar.setSize(sf::Vector2f(12.f, 12.f));
        setBackground(Palette::gray_dark);
    }

    virtual bool update(const sf::Vector2i& mpos) override
    {
        bool cnt = Scrollable::contains(mpos);
        switch (state) {
            default:
                // this should never happen, log this
                setState(READY);
                [[fallthrough]]; // just in case, process as normal
            case READY:
                if (cnt) {
                    setState(HIGHLIGHTED);
                }
                else {
                    break;
                }
                [[fallthrough]]; // allow same-frame update when the mouse enters the frame
            case HIGHLIGHTED:
                if (cnt) {
                    sf::Vector2i trans_pos(translateGlobalPos(mpos));
                    if (highlighted_row && highlighted_row != active_row && highlighted_row->button.update(trans_pos)) {
                        break;
                    }
                    else {
                        highlighted_row = nullptr;
                        if (active_row && active_row->button.contains(trans_pos)) {
                            highlighted_row = active_row;
                            break;
                        }
                        for (auto& row : rows) {
                            if (&row != active_row && row.button.update(trans_pos)) {
                                highlighted_row = &row;
                            }
                        }
                    }
                }
                else {
                    setState(READY);
                    if (highlighted_row) {
                        if (highlighted_row != active_row) {
                            highlighted_row->button.setToBase();
                        }
                        highlighted_row = nullptr;
                    }
                }
                break;
        }
        return cnt;
    }

    virtual void clickLeft() override
    {
        if (!highlighted_row) {
            deactivate();
        }
        else if (highlighted_row != active_row) {
            if (active_row) {
                active_row->button.setToBase();
            }
            active_row = highlighted_row;
            active_row->button.setState(ACTIVE);
            activate();
        }
        else if (state == READY) {
            if (active_row) {
                active_row->button.setState(READY);
                deactivate();
            }
        }
    }

    virtual void releaseLeft() override
    {}

    virtual void keyPressed(sf::Keyboard::Key k) override
    {
        if (k == sf::Keyboard::Escape) {
            deactivate();
        }
    }

    virtual void clickRight() override
    {
        deactivate();
    }

    virtual void activate() override
    {
        Menu_Element::activate();
        setState(ACTIVE);
    }

    virtual void deactivate() override
    {
        if (active_row) {
            active_row->button.deactivate();
            active_row = nullptr;
        }
        Menu_Element::deactivate();
    }

    virtual void scroll(float delta) override
    {
        Scrollable::scroll(delta, sf::Vector2f(sf::Mouse::getPosition()));
    }

    std::vector<T> getData()
    {
        std::vector<T> data;
        for (const auto& row : rows) {
            data.push_back(row.data);
        }
        return data;
    }
/*
    void load(std::vector<T> data)
    {
        reset();
        commands = new_commands;
        rows.clear();

        float button_offset = 32.f;

        sf::Vector2f pos(button_offset, button_offset);

        for (auto& c : commands) {
            std::string key = key_string.toString(c.key);

            sf::Vector2f button_pos(pos);
            sf::Vector2f button_size = sf::Vector2f(192.f, 128.f);

            Button button(key, font, csize, Button::READY);
            button.setSize(button_size);
            button.setPosition(button_pos);

            sf::Text text;
            text.setFont(font);
            text.setString(c.press);
            text.setCharacterSize(csize);
            centerText(text);

            sf::Vector2f text_pos(button_pos + (button_size / 2.f));
            text_pos.x += button_size.x + button_offset;
            text_pos.x += (text.getGlobalBounds().left + text.getGlobalBounds().width) / 2.f;
            text.setPosition(text_pos);

            rows.push_back(std::make_tuple(text, std::make_unique<Button>(button), &c));

            pos.y += button_size.y + button_offset;
        }

        setScrollable(pos.y);
    }
*/
protected:
    struct Row {
        sf::Sprite sprite;
        Button button;
        sf::Text text;
        T data;
    };

    std::vector<Row> rows;

    Row* highlighted_row { nullptr };
    Row* active_row { nullptr };

    constexpr static unsigned int csize { 44 };
    constexpr static unsigned int text_size { 42 };

    const sf::Font& font;

    constexpr static float button_offset { 16.f };

    sf::Vector2f button_size { 0.f, 0.f };
    sf::Vector2f button_pos { 0.f, 0.f };

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.setView(view);
        target.draw(background, states);
        for (const auto& r : rows) {
            target.draw(r.sprite, states);
            target.draw(r.button, states);
            target.draw(r.text, states);
        }
        target.draw(scrollbar, states);
    }
};
