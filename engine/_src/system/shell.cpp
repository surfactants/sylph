#include <system/shell.hpp>

Shell::Shell()
    : window { sf::VideoMode::getDesktopMode(), "sylph x", sf::Style::Fullscreen }
{
    window.setKeyRepeatEnabled(false);
    window.setVerticalSyncEnabled(true);
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
