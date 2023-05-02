#pragma once

#include "game.hpp"

class Game_Play : public Game {
public:
    Game_Play();

    ~Game_Play();

    virtual void update(float delta_time, const sf::Vector2f& mpos) override;

    virtual void clickLeft() override;
    virtual void releaseLeft() override;
    virtual void clickRight() override;
    virtual void releaseRight() override;

private:
    sf::View map_view;
};
