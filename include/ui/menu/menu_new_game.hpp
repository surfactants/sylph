#pragma once

#include <game/data/new_game_data.hpp>

#include "menu.hpp"

class Menu_New_Game : public Menu {
public:
    Menu_New_Game(std::function<void(New_Game_Data)> start_game);

    virtual void exitState() override;

    virtual bool handleInput(const sf::Event& event) override;

    void start();
    void cancel();

    std::function<void(New_Game_Data)> start_game;

protected:
    bool validate(); // checks that the game is ready to start (everything necessary has been set)

    // THESE SHOULD BE MAPS! the keys will determine where the data goes on new game creation
    std::vector<Color_Selector> selectors;
    std::vector<Simple_Textbox> textboxes;

    bool valid { false };
};
