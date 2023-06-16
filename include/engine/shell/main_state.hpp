#pragma once

#include <SFML/Graphics.hpp>

#include <functional>

class Main_State : public sf::Drawable {
public:
    Main_State();

    enum State {
        MENU,
        NEW_GAME,
        LOAD_GAME,
        GAME,
        QUIT
    };

    virtual void update(const float delta_time) = 0;
    virtual void handleInput(const sf::Event& event) = 0;

    virtual void windowResize(const sf::Vector2u& w_size) = 0;

    static std::function<void(Main_State::State)> setState;

protected:
    std::vector<const sf::Drawable*> drawables;

    sf::View view;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
