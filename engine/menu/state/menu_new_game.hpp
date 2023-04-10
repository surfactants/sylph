#pragma once

#include "menu.hpp"

class Menu_New_Game : public Menu {
public:
    Menu_New_Game();

    virtual void enterState() override;
    virtual void exitState() override;

    virtual void handleInput(const sf::Event& event) override;

    void start();
    void cancel();

protected:
    bool validate(); // checks that the game is ready to start (everything necessary has been set)

    // THESE SHOULD BE MAPS! the keys will determine where the data goes on new game creation
    std::vector<Color_Selector> selectors;
    std::vector<Simple_Textbox> textboxes;
};
