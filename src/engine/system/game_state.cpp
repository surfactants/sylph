#include <engine/system/game_state.hpp>

#include <engine/database/database_commands.hpp>

#include <game/state/new_game.hpp>
#include <game/state/game_play.hpp>

#include <ui/ui_hud.hpp>

Game_State::Game_State(std::function<void()> open_pause)
{
    //registerComponent<Entity_Info>();
    //registerComponent<Color>();
    registerComponent<Transform>();
    registerComponent<Collision_Rect>();
    registerComponent<Polygon_Tile>();
    registerComponent<Hierarchy>();
    registerComponent<Tile>();
    registerComponent<Body_Info>();

    // loadCommands handles permanent functions but open_pause is carried over in the newly-defined input package
    input_map[Game::PLAY].addPress(sf::Keyboard::Escape, open_pause);

    Game::setGameState = std::bind(setGameState, this, std::placeholders::_1);
    New_Game::newToPlay = std::bind(newToPlay, this);

    UI::setGameState = std::bind(setGameState, this, std::placeholders::_1);
    UI::openPause = open_pause;

    Game::systems.camera_controller.view = &view;
}

void Game_State::clickLeft()
{
    // attempt UI input first
    game->clickLeft();
}

void Game_State::releaseLeft()
{
    game->releaseLeft();
}

void Game_State::clickRight()
{
    // attempt UI input first
    game->clickRight();
}

void Game_State::releaseRight()
{
    game->releaseRight();
}

void Game_State::clickMiddle()
{
    // attempt UI input first
    game->clickMiddle();
}

void Game_State::releaseMiddle()
{
    game->releaseMiddle();
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
            input->scroll(event.mouseWheelScroll.delta);
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
    for (const auto& c : commands) {
        if (c.key != sf::Keyboard::Unknown) {
            ig->addPress(c.key, stringToFunction(c.press));
            ig->addRelease(c.key, stringToFunction(c.release));
        }
    }

    // must re-add permanent options
    ig->addPress(sf::Keyboard::Escape, open_pause);

    ig->addPress(sf::Mouse::Left, std::bind(clickLeft, this));
    ig->addRelease(sf::Mouse::Left, std::bind(releaseLeft, this));

    ig->addPress(sf::Mouse::Right, std::bind(clickRight, this));
    ig->addRelease(sf::Mouse::Right, std::bind(releaseRight, this));

    ig->addPress(sf::Mouse::Middle, std::bind(clickMiddle, this));
    ig->addRelease(sf::Mouse::Middle, std::bind(releaseMiddle, this));

    ig->scroll = std::bind(&Camera_Controller::zoomImpulse, &Game::systems.camera_controller, std::placeholders::_1);

    loadNums();
    // TODO: deprecate current num setup
    // either set up a conditional which passes the number to the function
    // or attempt to pass a char for all keyboard functions (yuck?)
    // or figure something else out.....
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
    auto acc = &Game::systems.accelerator;
    static std::map<std::string, std::function<void()>> func {
        // movement functions
        { "null", []() {} },
        { "move up", std::bind(&Input_Accelerator::startUp,         acc) },
        { "stop up", std::bind(&Input_Accelerator::stopUp,          acc) },
        { "move left", std::bind(&Input_Accelerator::startLeft,     acc) },
        { "stop left", std::bind(&Input_Accelerator::stopLeft,      acc) },
        { "move down", std::bind(&Input_Accelerator::startDown,     acc) },
        { "stop down", std::bind(&Input_Accelerator::stopDown,      acc) },
        { "move right", std::bind(&Input_Accelerator::startRight,   acc) },
        { "stop right", std::bind(&Input_Accelerator::stopRight,    acc) },

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
        { "switch maps", std::bind(&Context::toggle, &Game::systems.context) },

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
    game = std::make_unique<Game_Play>();

    ui = std::make_unique<UI_HUD>(Game::systems);

    Database_Commands dbc;
    loadCommands(dbc.read());

    drawables.clear();
    drawables.push_back(&Game::systems.renderer);
    drawables.push_back(ui.get());

    loadNums();

    setGameState(Game::PLAY);
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

void Game_State::windowResize(const sf::Vector2u& w_size)
{
    UI::setView(w_size);
    if (ui) {
        ui->windowResize(w_size);
    }
    Game::systems.windowResize(w_size);
}
