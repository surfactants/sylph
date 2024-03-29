#pragma once

#include <SFML/System/Clock.hpp>

class Double_Click {
public:
    bool operator () ()
    {
        bool dbl = (flag && timer.getElapsedTime().asSeconds() <= threshold);
        timer.restart();
        if (dbl) {
            flag = false;
        }
        else {
            flag = true;
        }
        return dbl;
    }
private:
    sf::Clock timer;
    constexpr static float threshold { 0.5f };
    bool flag { false };
};
