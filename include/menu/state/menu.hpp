#pragma once

#include <SFML/Graphics.hpp>

#include <variant>

#include <engine/event/event_bus.hpp>
#include <engine/system/main_state.hpp>

#include <menu/elements.hpp>

// make update virtual but continue to provide a base method which checks the nav

class Menu : public sf::Drawable {
public:
    Menu();

    enum State {
        MAIN = 0,
        PAUSE = 1,
        SETTINGS,
        SETTINGS_GAME,
        SETTINGS_GENERAL,
        SETTINGS_AUDIO,
        SETTINGS_KEYMAPPER,
        NEW_GAME,
        LOAD_GAME,
        SAVE_GAME,
        NULL_STATE
    };

    static void setView(const sf::Vector2u& w_size);
    virtual void windowResize(const sf::Vector2u& w_size) {} // todo make this pure virtual

    virtual void update(const sf::Vector2i& mpos);
    virtual void clickLeft();
    virtual void releaseLeft();
    void escape();
    virtual void clickRight();
    virtual void releaseRight();

    virtual void handleInput(const sf::Event& event);
    virtual void textEntered(const sf::Event& event);
    virtual void keyPressed(sf::Keyboard::Key key);

    virtual void enterState() {};
    virtual void exitState() {};

    virtual void save() { }

    void reset();

    // menu reversion is defined with operator() to act as a visitor in ::escape()
    void operator()(Menu::State state)
    {
        setMenuState(state);
    }
    void operator()(Main_State::State state)
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

    constexpr static unsigned int nav_csize { 72 };

    const static sf::Vector2f button_start;
    constexpr static float button_offset { 32.f };
    constexpr static float slider_offset { 128.f };

    const static sf::Vector2f nav_size;

    void addNav(std::string text, std::function<void()> target, Menu_Element::State base = Menu_Element::READY);
    void placeNav();

    std::variant<Menu::State, Main_State::State> escape_target;

    static Menu_Element* moused_element;
    static Menu_Element* active_element;

    static void setActive(Menu_Element* element);
    static void unsetActive(Menu_Element* element);

    static sf::View view;

    void clearNullElements();

    std::unique_ptr<Dialog> dialog { nullptr };

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
