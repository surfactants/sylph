#include <engine/system/game_state.hpp>

#include <engine/database/database_commands.hpp>

#include <game/state/new_game.hpp>
#include <game/state/game_play.hpp>

#include <iostream>

Game_State::Game_State(std::function<void()> open_pause)
{
    accelerator.setMaxSpeed(10.f);
    accelerator.setAcceleration(1.f);

    input_map[Game::PLAY].addPress(sf::Keyboard::Escape, open_pause);
    Database_Commands dbc;
    loadCommands(dbc.read());

    Game::setGameState = std::bind(setGameState, this, std::placeholders::_1);
    New_Game::newToPlay = std::bind(newToPlay, this);

    window_frame.left = 0.f;
    window_frame.top = 0.f;
    window_frame.width = 1920.f;
    window_frame.height = 1080.f;
}

void Game_State::update(float delta_time)
{
    sf::Vector2f velocity = accelerator.update(delta_time) * (zoom * 2.f);
    moveFrame(velocity);
    game->update(delta_time, relativeMousePos(view));
}

void Game_State::moveFrame(sf::Vector2f& velocity)
{
    sf::Vector2f min = game->getWorld()->min;
    sf::Vector2f max = game->getWorld()->max - sf::Vector2f(window_frame.width, window_frame.height);
    sf::Vector2f fpos(window_frame.left + velocity.x, window_frame.top + velocity.y);

    if (fpos.x < min.x) {
        velocity.x = min.x - window_frame.left;
        fpos.x = min.x;
    }
    else if (fpos.x > max.x) {
        velocity.x = max.x - window_frame.left;
        fpos.x = max.x;
    }

    if (fpos.y < min.y) {
        velocity.y = min.y - window_frame.top;
    }
    else if (fpos.y > max.y) {
        velocity.y = max.y - window_frame.top;
    }

    view.move(velocity);
    window_frame.left += velocity.x;
    window_frame.top += velocity.y;
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
            scroll(event.mouseWheelScroll.delta);
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

void Game_State::scroll(float delta)
{
    float target;
    if (delta < 0.f && zoom < max_zoom) {
        // zoom out
        target = zoom + zoom_step;
    }
    else if (delta > 0.f && zoom > min_zoom) {
        // zoom in
        target = zoom - zoom_step;
    }
    else {
        return;
    }

    float factor = (target / zoom);
    view.zoom(factor);
    zoom *= factor;

    window_frame = sf::FloatRect(view.getCenter() - (view.getSize() / 2.f), view.getSize());
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
        ig->addPress(converter.toKey(num), std::bind(numPress, this, i));
    }
}

void Game_State::numPress(unsigned int i)
{
    game->getWorld()->eraseCell(i);
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
    // i.e. use Game_State functions
    //
    static std::map<std::string, std::function<void()>> func {
        // movement functions
        { "null", []() {} },
        { "move up", std::bind(&Accelerator::startUp, &accelerator) },
        { "stop up", std::bind(&Accelerator::stopUp, &accelerator) },
        { "move left", std::bind(&Accelerator::startLeft, &accelerator) },
        { "stop left", std::bind(&Accelerator::stopLeft, &accelerator) },
        { "move down", std::bind(&Accelerator::startDown, &accelerator) },
        { "stop down", std::bind(&Accelerator::stopDown, &accelerator) },
        { "move right", std::bind(&Accelerator::startRight, &accelerator) },
        { "stop right", std::bind(&Accelerator::stopRight, &accelerator) },

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
