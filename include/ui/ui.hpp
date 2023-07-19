#pragma once

#include <SFML/Graphics.hpp>

#include <variant>

#include <engine/event/event_bus.hpp>

#include <engine/shell/main_state.hpp>

#include <game/core/ecs_core.hpp>

#include <game/state/game.hpp>

#include "elements/elements.hpp"

#include "strings/localizer.hpp"

class UI : public sf::Drawable {
public:
    UI();

    enum State {
        // MENU STATES
        TITLE = 0,
        PAUSE = 1,
        SETTINGS,
        SETTINGS_GAME,
        SETTINGS_GENERAL,
        SETTINGS_AUDIO,
        SETTINGS_KEYMAPPER,
        NEW_GAME,
        LOAD_GAME,
        SAVE_GAME,

        // HUD STATES
        NULL_STATE
    };

    virtual void update(const sf::Vector2i& mpos);
    virtual bool handleInput(const sf::Event& event);

    virtual bool clickLeft();
    virtual bool clickRight();
    virtual bool releaseLeft();
    virtual bool releaseRight();
    virtual bool scroll(const float delta);

    virtual bool keyPressed(sf::Keyboard::Key key);
    virtual bool textEntered(const sf::Event& event);
    virtual void escape();
    virtual void confirm() { }

    virtual void reset();

    virtual void enterState() { }
    virtual void exitState()  { }

    static std::function<void(Game::State)> setGameState;
    static std::function<void()> openPause;

    template <typename T>
    static inline std::function<T(Entity)> getComponent;

    static std::function<void(Main_State::State)> setMainState;
    static std::function<void(UI::State)> setUIState;

    void setEscape(UI::State state);
    void setEscape(Main_State::State state);

    static void setView(const sf::Vector2u& w_size);
    virtual void windowResize(const sf::Vector2u& w_size) = 0;

    static std::function<void()> clearGame;

    // defined to act as a visitor in ::escape()
    void operator()(UI::State state)
    {
        setUIState(state);
    }

    void operator()(Main_State::State state)
    {
        setMainState(state);
    }

protected:
    static Renderer renderer;
    static sf::View view;

    static Element* moused;
    static Element* active;

    static void setActive(Element* element);
    static void unsetActive(Element* element);

    std::vector<Element*> elements;

    std::variant<UI::State, Main_State::State> escape_target;

    void clearNullElements();

    std::unique_ptr<Dialog> dialog { nullptr };

    static Localizer localize;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
