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
    bool validate();
    Color_Selector selector;
    // need a method for checking readiness
    // i.e. don't let a player start without a name, etc
};
