#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <functional>
#include <map>
#include <string>
/*
struct Command {
    sf::Keyboard::Key k;
    std::string pressed;
    std::string released;
};
*/
class Input_Package {
public:
    Input_Package() = default;

    void addPress(sf::Keyboard::Key k, std::function<void()> func);
    void addPress(sf::Mouse::Button b, std::function<void()> func);

    void addRelease(sf::Keyboard::Key k, std::function<void()> func);
    void addRelease(sf::Mouse::Button b, std::function<void()> func);

    void press(sf::Keyboard::Key k);
    void press(sf::Mouse::Button b);

    void release(sf::Keyboard::Key k);
    void release(sf::Mouse::Button b);

private:
    std::map<sf::Keyboard::Key, std::function<void()>> key_press;
    std::map<sf::Keyboard::Key, std::function<void()>> key_release;

    std::map<sf::Mouse::Button, std::function<void()>> mouse_press;
    std::map<sf::Mouse::Button, std::function<void()>> mouse_release;
};
