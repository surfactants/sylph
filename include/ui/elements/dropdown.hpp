#pragma once

#include "button.hpp"
#include "scrollable.hpp"

#include <iostream>

/// DROPDOWN ///
/// \brief a dropdown menu for selecting one of many options. uses a view-based scrollbar (Scrollable option_frame).
/// The templated type is what the options themselves store. setView() and load() MUST be called, IN THAT ORDER.
///

/* NOTES
 *
 * STATE
 * * The base Button is used to access the menu and display the selected element
 * * READY and HIGHLIGHTED states correspond to the base Button's states
 * * ACTIVE state indicates that the menu is open
 * * * While active, state check is performed on the Options
 * * * Active and moused options are tracked by two pointers (active_option, moused_option) for simpler parsing that can sometimes bypass iteration
 *
 * OPTION
 * The Dropdown uses a specialized Button, called Option:
 * * Holds T variable (one per option)
 * * Only overrided function is update, which removes the ACTIVE case (ACTIVE tracking is handled by Dropdown-level clicks)
 *
 */

template <typename T>
class Dropdown : public Button {
protected:
    class Option : public Button {
    public:
        Option() = default;
        Option(std::string label, const sf::Font& font, unsigned int csize, State base)
            : Button(label, font, csize, base)
        {}

        T data;

        virtual bool update(const sf::Vector2i& mpos) override
        {
            bool cnt = contains(mpos);

            if (cnt) {
                switch (state) {
                    case READY:
                        if (cnt) {
                            Button::setState(HIGHLIGHTED);
                        }
                        break;
                    case HIGHLIGHTED:
                        if (!cnt) {
                            Button::setState(READY);
                        }
                        break;
                    default:
                        break;
                }
            }

            return cnt;
        }
    };

public:
    Dropdown()
    {
        base_state = READY;
        setState(READY);
    }

    constexpr static float padding = 2.f;

    virtual void setPosition(const sf::Vector2f& pos)
    {
        Button::setPosition(pos);
        option_frame.setPosition(pos);
    }

    void setView(sf::Vector2f pos, sf::Vector2f size, sf::Vector2u window_size)
    {
        frame.setPosition(pos);
        pos -= sf::Vector2f(padding, padding); // offset the view so the buttons match
        option_frame.setView(pos, size, window_size);
        option_frame.setScrollable(size.y * 2.f);
        option_frame.setBackground(Palette::gray_dark);
    }

    void load(std::vector<std::pair<std::string, T>> data, const sf::Font& font, unsigned int csize, size_t current)
    {
        sf::Vector2f view_size = option_frame.getSize();
        sf::Vector2f total_size(view_size.x - option_frame.scrollbarSize().x, padding);
        const sf::Vector2f option_size(total_size.x - (padding * 2.f), 96.f);

        sf::Vector2f option_pos(padding, padding);

        for (const auto& d : data) {
            options.push_back(Option(d.first, font, csize, READY));
            options.back().data = d.second;
            options.back().setPosition(option_pos);
            options.back().setSize(option_size);
            option_pos.y += option_size.y + padding;
            total_size.y += option_size.y + padding;
        }

        options[current].setState(ACTIVE);
        active_option = &options[current];

        setSize(option_size);
        label.setFont(font);
        label.setCharacterSize(csize);
        setLabel(options[current].getLabel());

        setSize(option_size);

        option_frame.setScrollable(total_size.y);

        setSize(option_size);
    }

    virtual bool update(const sf::Vector2i& mpos) override // needs to translate mpos if active
    {
        bool cnt = contains(mpos);

        switch (state) {
            case READY:
                if (cnt) {
                    setState(HIGHLIGHTED);
                }
                break;
            case HIGHLIGHTED:
                if (!cnt) {
                    setState(READY);
                }
                break;
            case ACTIVE:
                cnt = activeUpdate(mpos);
                break;
            default:
                break;
        }

        return cnt;
    }

    virtual bool clickLeft() override
    {
        switch (state) {
            case HIGHLIGHTED:
                // open on highlight
                activate();
                return true;
            case ACTIVE:
                if (moused_option) {
                    if (moused_option->active()) {
                        deactivate();
                    }
                    else {
                        set(moused_option);
                    }
                    return true;
                }
                else {
                    deactivate();
                    return false;
                }
            default:
                return false;
        }
    }

    virtual void activate() override
    {
        scrollToActive();
        setState(ACTIVE);
        Element::activate();
    }

    virtual bool releaseLeft() override
    {
        return (moused_option);
    }

    virtual bool clickRight() override
    {
        if (active()) {
            deactivate();
            return true;
        }
        return false;
    }

    virtual void deactivate() override
    {
        Element::deactivate();
        resetMousedOption();
        setToBase();
    }

    T selected()
    {
        return active_option->data;
    }

    virtual void scroll(float delta)
    {
        option_frame.scroll(delta, sf::Vector2f(sf::Mouse::getPosition()));
    }

    virtual bool keyPressed(sf::Keyboard::Key key)
    {
        if (key == sf::Keyboard::Escape) {
            deactivate();
            return true;
        }
        return false;
    }

    void set(T t)
    {
        for (auto& o : options) {
            if (o.data == t) {
                set(&o);
                return;
            }
        }
        // log failure to return
    }

    void set(Option* o)
    {
        active_option->setToBase();
        o->setState(ACTIVE);
        setLabel(o->getLabel());
        active_option = o;
    }

    void set(unsigned int index)
    {
        if (index >= options.size()) {
            index = 0;
        }
        active_option->setToBase();
        options[0].setState(ACTIVE);
        setLabel(options[0].getLabel());
        active_option = &options[0];
    }

    void scrollToActive()
    {
        // TODO
    }

protected:
    Scrollable option_frame;

    std::vector<Option> options;

    size_t render_index { 0 };
    size_t render_size { 5 };

    Option* active_option { nullptr };
    Option* moused_option { nullptr };

    sf::RectangleShape option_bg;

    bool activeUpdate(sf::Vector2i mpos)
    {
        bool cnt = option_frame.contains(mpos);
        if (cnt) {
            mpos = option_frame.translateGlobalPos(mpos);
            if (moused_option && moused_option->update(mpos)) {
                // - free space - //
            }
            else {
                resetMousedOption();
                for (auto& o : options) {
                    if (o.update(mpos)) {
                        moused_option = &o;
                    }
                }
            }
        }
        else {
            resetMousedOption();
        }
        std::cout << "active update\n";
        return true;
    }

    void resetMousedOption()
    {
        if (moused_option && !moused_option->active()) {
            moused_option->setToBase();
            moused_option = nullptr;
        }
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        switch (state) {
            case ACTIVE:
                target.draw(option_frame, states);
                for (const auto& o : options) {
                    target.draw(o, states);
                }
                break;
            case HIGHLIGHTED:
                [[fallthrough]];
            case READY:
                target.draw(frame, states);
                target.draw(label, states);
                break;
            default:
                break;
        }
    }
};
