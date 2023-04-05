#include <system/shell.hpp>

#include <system/database/database_commands.hpp>
#include <system/input/command.hpp>

Shell::Shell()
    : window { sf::VideoMode::getDesktopMode(), "sylph x", sf::Style::Fullscreen }
{
    window.setKeyRepeatEnabled(false);
    window.setVerticalSyncEnabled(true);

    std::vector<Command> c;

    c.push_back(Command());
    c.back().key = sf::Keyboard::W;
    c.back().press = "move north";
    c.back().release = "stop north";

    c.push_back(Command());
    c.back().key = sf::Keyboard::A;
    c.back().press = "move west";
    c.back().release = "stop west";

    c.push_back(Command());
    c.back().key = sf::Keyboard::X;
    c.back().press = "move south";
    c.back().release = "stop south";

    c.push_back(Command());
    c.back().key = sf::Keyboard::D;
    c.back().press = "move east";
    c.back().release = "stop east";

    Database_Commands dbc;

    dbc.write(c);
}

void Shell::run()
{
    while (window.isOpen()) {
        update();
        draw();
    }
}

void Shell::update()
{
    while (window.pollEvent(event)) {
        state.handleInput(event);
    }
    state.update(1.f);
    audio.update();
}

void Shell::draw()
{
    window.clear();
    window.draw(state);
    window.display();
}
