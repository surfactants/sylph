#pragma once

#include <game/data/new_game_data.hpp>

#include "panels/new_game_base_panel.hpp"

#include "menu.hpp"

class Menu_New_Game : public Menu {
public:
    Menu_New_Game(std::function<void(New_Game_Data)> start_game);

    virtual void exitState() override;

    virtual bool handleInput(const sf::Event& event) override;
    virtual bool keyPressed(sf::Keyboard::Key key) override;

    virtual void confirm() override;
    void cancel();

    std::function<void(New_Game_Data)> start_game;

protected:
    bool validate(); // checks that the game is ready to start (everything necessary has been set)

    std::unique_ptr<Tabbed_Panel> panels { nullptr };

    std::shared_ptr<Base_Panel> base { nullptr };

    // textboxes are stored here for simple validation
    std::vector<std::shared_ptr<Simple_Textbox>> textboxes;

    bool valid { false };
};
