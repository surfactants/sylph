#include <system/input/input_package.hpp>

void Input_Package::addPress(sf::Keyboard::Key k, std::function<void()> func)
{
    key_press[k] = func;
}

void Input_Package::addPress(sf::Mouse::Button b, std::function<void()> func)
{
    mouse_press[b] = func;
}

void Input_Package::addRelease(sf::Keyboard::Key k, std::function<void()> func)
{
    key_release[k] = func;
}

void Input_Package::addRelease(sf::Mouse::Button b, std::function<void()> func)
{
    mouse_release[b] = func;
}

void Input_Package::press(sf::Keyboard::Key k)
{
    if (key_press.contains(k)) {
        key_press[k]();
    }
}

void Input_Package::press(sf::Mouse::Button b)
{
    if (mouse_press.contains(b)) {
        mouse_press[b]();
    }
}

void Input_Package::release(sf::Keyboard::Key k)
{
    if (key_release.contains(k)) {
        key_release[k]();
    }
}

void Input_Package::release(sf::Mouse::Button b)
{
    if (mouse_release.contains(b)) {
        mouse_release[b]();
    }
}
