#include <system/main_state/game_state.hpp>

#include <game/game_play.hpp>

#include <system/database/database_commands.hpp>

Game_State::Game_State(std::function<void()> open_pause)
{
    input_map[Game::PLAY].addPress(sf::Keyboard::Escape, open_pause);
    Database_Commands dbc;
    loadCommands(dbc.read());
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

std::vector<Command> Game_State::getCommands()
{
    return commands;
}

void Game_State::loadCommands(std::vector<Command> new_commands)
{
    commands = new_commands;
    Input_Package* ig = &input_map[Game::PLAY];
    auto open_pause = ig->key_press[sf::Keyboard::Escape];
    ig->clear();
    ig->addPress(sf::Keyboard::Escape, open_pause);
    for (const auto& c : commands) {
        if (c.key != sf::Keyboard::Unknown) {
            ig->addPress(c.key, stringToFunction(c.press));
            ig->addRelease(c.key, stringToFunction(c.release));
        }
    }
}

std::function<void()> Game_State::stringToFunction(std::string str)
{
    // here, match the game functions to string identifiers
    static std::map<std::string, std::function<void()>> func
    {
        { "move north", [](){} },
        { "stop north", [](){} },
        { "move west", [](){} },
        { "stop west", [](){} },
        { "move south", [](){} },
        { "stop south", [](){} },
        { "move east", [](){}  },
        { "stop east", [](){}  }
    };

    if (func.contains(str)) {
        return func[str];
    }

    // log failure to find command

    return [](){};
}

void Game_State::setGameState(Game::State new_game)
{
    game = states[new_game].get();
    input = &input_map[new_game];
}
