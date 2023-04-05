#include <system/main_state/game_state.hpp>

#include <game/game_play.hpp>

Game_State::Game_State(std::function<void()> open_pause)
{
    input_map[Game::PLAY].addPress(sf::Keyboard::Escape, open_pause);
    states[Game::PLAY] = std::make_unique<Game_Play>();

    setGameState(Game::PLAY);
}

void Game_State::update(float delta_time)
{}

void Game_State::handleInput(const sf::Event& event)
{
    switch (event.type) {
        case sf::Event::MouseButtonPressed:
            input->press(event.mouseButton.button);
            break;
        case sf::Event::MouseButtonReleased:
            input->release(event.mouseButton.button);
            break;
        case sf::Event::MouseWheelScrolled:
            break;
        case sf::Event::KeyPressed:
            input->press(event.key.code);
            break;
        case sf::Event::KeyReleased:
            input->release(event.key.code);
            break;
        case sf::Event::LostFocus:
            // pause
            break;
        case sf::Event::GainedFocus:
            // unpause IF paused by a lostfocus event
            // add a flag in Game_Pause
            break;
        default:
            break;
    }
}

void Game_State::setGameState(Game::State new_game)
{
    game = states[new_game].get();
    input = &input_map[new_game];
}
