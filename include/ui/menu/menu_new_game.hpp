#pragma once

#include <game/data/new_game_data.hpp>

#include "panels/civ_panel.hpp"
#include "panels/home_panel.hpp"
#include "panels/species_panel.hpp"

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

    std::shared_ptr<Species_Panel> species { nullptr };
    std::shared_ptr<Home_Panel> home { nullptr };
    std::shared_ptr<Civ_Panel> civ { nullptr };

    std::vector<std::shared_ptr<Simple_Textbox>> textboxes;

    bool valid { false };
};
