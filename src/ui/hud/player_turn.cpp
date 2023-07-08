#include <ui/hud/player_turn.hpp>

Player_Turn::Player_Turn()
{
    std::string text = "NEXT_TURN";
    std::string loc = localize(text);
    next_turn = std::make_shared<Button>(loc, *font, std::bind(nextTurn, this), 40);
    sf::Text* ptr = next_turn->getText();
    localize.recordPersistent(text, ptr);
}

void Player_Turn::enterState()
{
    turn_panel->addElement(next_turn.get(), Panel::CENTER);
}

void Player_Turn::nextTurn()
{
    setHUDState(HUD::AI_TURN);
    // effect game state change here too...?
}

void Player_Turn::windowResize(const sf::Vector2u& w_size)
{
    HUD::windowResize(w_size);
    sf::Vector2f panel_size = turn_panel->getSize();
    sf::Vector2f button_size = next_turn->getSize();
    sf::Vector2f next_pos = turn_panel->getPosition();

    float padding = (panel_size.x - button_size.x) / 2.f;
    next_pos.x += padding;
    next_pos.y += (panel_size.y - button_size.y - padding);

    next_turn->setPosition(next_pos);
}
