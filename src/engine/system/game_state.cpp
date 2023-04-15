#include <engine/system/game_state.hpp>

#include <engine/database/database_commands.hpp>

#include <game/state/new_game.hpp>
#include <game/state/game_play.hpp>

Game_State::Game_State(std::function<void()> open_pause)
{
    input_map[Game::PLAY].addPress(sf::Keyboard::Escape, open_pause);
    Database_Commands dbc;
    loadCommands(dbc.read());
    states[Game::PLAY] = std::make_unique<Game_Play>();

    Game::setGameState = std::bind(setGameState, this, std::placeholders::_1);
    New_Game::newToPlay = std::bind(newToPlay, this);
}

void Game_State::update(float delta_time)
{
    game->update(delta_time);
}

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

void Game_State::loadSettings(Game_Settings settings)
{
    this->settings = settings;
    if (game) {
        game->loadSettings(settings);
    }
}

std::function<void()> Game_State::stringToFunction(std::string str)
{
    // here, match the game functions to string identifiers
    // use std::bind - the lambdas are placeholders
    static std::map<std::string, std::function<void()>> func
    {
        // movement functions
        { "null",       []() {} },
        { "move north", []() {} },
        { "stop north", []() {} },
        { "move west",  []() {} },
        { "stop west",  []() {} },
        { "move south", []() {} },
        { "stop south", []() {} },
        { "move east",  []() {} },
        { "stop east",  []() {} },

        // ability functions
        { "start ability 1", []() {} },
        { "stop ability 1",  []() {} },
        { "start ability 2", []() {} },
        { "stop ability 2",  []() {} },
        { "start ability 3", []() {} },
        { "stop ability 3",  []() {} },
        { "start ability 4", []() {} },
        { "stop ability 4",  []() {} },

        // world
        { "start interact", []() {} },
        { "stop interact",  []() {} },

        // ui
        { "open inventory", []() {} }
    };

    if (func.contains(str)) {
        return func[str];
    }

    // log failure to find command

    return [](){};
}

void Game_State::newGame(New_Game_Data data)
{
    game = std::make_unique<New_Game>(data);
    setGameState(Game::NEW);
}

void Game_State::newToPlay()
{
    Game_Play g(*game);
    game = nullptr;
    game = std::make_unique<Game_Play>(g);
    setGameState(Game::PLAY);
}

void Game_State::setGameState(Game::State state)
{
    game_state = state;
    input = &input_map[state];
}
