#pragma once

#include <game/core/entity.hpp>
#include <game/system/renderer.hpp>
#include <game/state/game.hpp>

#include <ui/elements/ui_element.hpp>
#include <ui/elements/elements.hpp>

class UI : public sf::Drawable {
public:
    UI();

    Renderer* getRenderer();

    virtual void update(const sf::Vector2i& mpos);
    virtual bool handleInput(const sf::Event& event);
    virtual void clickLeft();
    virtual void releaseLeft();
    virtual void clickRight();
    virtual void releaseRight();
    virtual void keyPressed(sf::Keyboard::Key key);
    virtual void textEntered(const sf::Event& event);
    virtual void escape();

    virtual void enterState() = 0;
    virtual void exitState() = 0;

    static std::function<void(Game::State)> setGameState;
    static std::function<void()> openPause;

    template <typename T>
    static inline std::function<T(Entity)> getComponent;

    static void setView(const sf::Vector2u& w_size);
    virtual void windowResize(const sf::Vector2u& w_size) = 0;

protected:
    static Renderer renderer;
    static sf::Font* font;
    static sf::View view;

    static UI_Element* moused_element;
    static UI_Element* active_element;

    static void setActive(UI_Element* element);
    static void unsetActive(UI_Element* element);

    std::vector<UI_Element*> elements;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
