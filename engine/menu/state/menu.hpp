#pragma once

#include <SFML/Graphics.hpp>

#include <variant>

#include <system/event/event_bus.hpp>
#include <system/main_state/main_state.hpp>

#include <menu/elements/button.hpp>
#include <menu/elements/color_selector.hpp>
#include <menu/elements/slider.hpp>
#include <menu/elements/simple_textbox.hpp>

// make update virtual but continue to provide a base method which checks the nav

class Menu : public sf::Drawable {
public:
    Menu();

    enum State {
        MAIN = 0,
        PAUSE = 1,
        SETTINGS,
        SETTINGS_GENERAL,
        SETTINGS_AUDIO,
        SETTINGS_KEYMAPPER,
        NEW_GAME,
        LOAD_GAME,
        SAVE_GAME,
        NULL_STATE
    };

    virtual void update(const sf::Vector2i& mpos);
    void clickLeft();
    void releaseLeft();
    void escape();
    virtual void clickRight();
    virtual void releaseRight();

    virtual void handleInput(const sf::Event& event);
    virtual void textEntered(const sf::Event& event);
    virtual void keyPressed(sf::Keyboard::Key key);

    virtual void enterState();
    virtual void exitState();

    virtual void save(){}

// menu reversion is defined with operator() to act as a visitor in ::escape()
    void operator ()(Menu::State state)
    {
        setMenuState(state);
    }
    void operator ()(Main_State::State state)
    {
        setMainState(state);
    }

    static std::function<void(Main_State::State)> setMainState;

    static std::function<void(Menu::State)> setMenuState;

    void setEscape(Menu::State state);
    void setEscape(Main_State::State states);

    static std::unique_ptr<sf::Font> font; // protect this (temporary for fps)

protected:
    std::vector<Menu_Element*> elements;
    std::vector<Button> nav;

    constexpr static unsigned int csize { 72 };

    const static sf::Vector2f button_start;
    constexpr static float button_offset { 32.f };
    constexpr static float slider_offset { 128.f };

    void placeNav();

    std::variant<Menu::State, Main_State::State> escape_target;

    Menu_Element* mouse_target { nullptr };
    Menu_Element* active_element { nullptr };

    void setActive(Menu_Element* element);
    void unsetActive();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
