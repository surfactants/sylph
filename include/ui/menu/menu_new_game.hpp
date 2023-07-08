#pragma once

#include <game/data/new_game_data.hpp>

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

    std::shared_ptr<Panel> species_panel { nullptr };
        std::shared_ptr<sf::Text> species_title { nullptr };
        std::shared_ptr<Simple_Textbox> tbox_species_name { nullptr };

    std::shared_ptr<Panel> home_panel { nullptr };
        std::shared_ptr<sf::Text> home_title { nullptr };
        std::shared_ptr<Simple_Textbox> tbox_star_name { nullptr };
        std::shared_ptr<Simple_Textbox> tbox_homeworld_name { nullptr };

    std::shared_ptr<Panel> civ_panel { nullptr };
        std::shared_ptr<sf::Text> civ_title { nullptr };
        std::shared_ptr<Simple_Textbox> tbox_civ_name { nullptr };
        std::shared_ptr<Color_Selector> civ_color;

    std::vector<std::shared_ptr<Simple_Textbox>> textboxes;

    bool valid { false };
};
