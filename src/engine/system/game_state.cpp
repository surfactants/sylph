#include <engine/system/game_state.hpp>

#include <engine/database/database_commands.hpp>

#include <game/state/new_game.hpp>
#include <game/state/game_play.hpp>

#include <iostream>

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

void Game_State::loadNums()
{
    Input_Package* ig = &input_map[Game::PLAY];
    Key_String converter;
    for (unsigned int i = 0; i < 10; i++) {
        std::string num = "Num" + std::to_string(i);
        ig->addPress(converter.toKey(num), [=]() {
            game->getWorld()->eraseCell(i);
        });
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
    // also, keep in mind that pointers could become an issue...
    // ... if casting between Game_Play and Game_UI
    // i.e. cache Game_Play and try to use Game_State functions
    // (ECS should handle it eventually with guaranteed persistent components)
    // (i.e. make
    //
    // (it will load a different input set on state change anyway,
    //  but don't take chances!
    static std::map<std::string, std::function<void()>> func {
        // movement functions
        { "null", []() {} },
        { "move north", []() {} },
        { "stop north", []() {} },
        { "move west", []() {} },
        { "stop west", []() {} },
        { "move south", []() {} },
        { "stop south", []() {} },
        { "move east", []() {} },
        { "stop east", []() {} },

        // ability functions
        { "start ability 1", []() {} },
        { "stop ability 1", []() {} },
        { "start ability 2", []() {} },
        { "stop ability 2", []() {} },
        { "start ability 3", []() {} },
        { "stop ability 3", []() {} },
        { "start ability 4", []() {} },
        { "stop ability 4", []() {} },

        // world
        { "start interact", []() {} },
        { "stop interact", []() {} },

        // ui
        { "open inventory", []() {} },

        // debug
        { "regenerate", std::bind(newGame, this, data) }
    };

    if (func.contains(str)) {
        return func[str];
    }

    // log failure to find command

    return []() {};
}

void Game_State::newGame(New_Game_Data data)
{
    game = std::make_unique<New_Game>(data);
    setGameState(Game::NEW);
}

void Game_State::newToPlay()
{
    std::unique_ptr<Game> g = std::make_unique<Game_Play>(*game);
    drawables.clear();
    game.reset();
    game = std::move(g);
    setGameState(Game::PLAY);
    std::cout << game->getWorld();
    drawables.push_back(game->getWorld());
    std::cout << "transitioned from new game to play state\n";

    loadNums();
}

void Game_State::setGameState(Game::State state)
{
    game_state = state;
    input = &input_map[state];
}

void Game_State::clear()
{
    game.reset();
    drawables.clear();
}
