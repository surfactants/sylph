#include <engine/shell/game_state.hpp>

#include <engine/database/database_commands.hpp>

#include <game/state/states.hpp>

#include <ui/hud/states.hpp>

Game_State::Game_State(std::function<void()> open_pause)
{
    // loadCommands handles permanent functions but open_pause is carried over in the newly-defined input package
    input.addPress(sf::Keyboard::Escape, open_pause);

    Game::setGameState = std::bind(setGameState, this, std::placeholders::_1);
    New_Game::newToPlay = std::bind(newToPlay, this);

    UI::setGameState = std::bind(setGameState, this, std::placeholders::_1);
    UI::openPause = open_pause;

    HUD::setHUDState = std::bind(setHUDState, this, std::placeholders::_1);

    // initialize hud states here
}

void Game_State::registration()
{
    Game::core->systems.camera_controller.view = &view;

    registerComponent<Collision_Rect>(Component::COLLISION_RECT);
    registerComponent<Entity_Data>(Component::ENTITY_DATA);
    registerComponent<Hierarchy>(Component::HIERARCHY);
    registerComponent<Transform>(Component::TRANSFORM);
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

void Game_State::scroll(const float delta)
{
    game->core->systems.camera_controller.zoomImpulse(delta);
}

void Game_State::update(const float delta_time)
{
    if (hud) {
        hud->update(sf::Mouse::getPosition());
    }
    game->update(delta_time);
}

void Game_State::handleInput(const sf::Event& event)
{
    if (hud && hud->handleInput(event)) {
        return;
    }
    switch (event.type) {
        case sf::Event::MouseButtonPressed:
            input.press(event.mouseButton.button);
            break;
        case sf::Event::MouseButtonReleased:
            input.release(event.mouseButton.button);
            break;
        case sf::Event::MouseWheelScrolled:
            input.scroll(event.mouseWheelScroll.delta);
            break;
        case sf::Event::KeyPressed:
            input.press(event.key.code);
            break;
        case sf::Event::KeyReleased:
            input.release(event.key.code);
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

void Game_State::loadCommands(std::vector<Command> commands)
{
    loadFunctions();
    auto open_pause = input.key_press[sf::Keyboard::Escape];
    input.clear();
    for (const auto& c : commands) {
        input.addPress(c.key, string_to_function[c.press]);
        input.addRelease(c.key, string_to_function[c.release]);
    }

    // must re-add permanent options
    input.addPress(sf::Keyboard::Escape, open_pause);

    input.addPress(sf::Mouse::Left, std::bind(clickLeft, this));
    input.addRelease(sf::Mouse::Left, std::bind(releaseLeft, this));

    input.addPress(sf::Mouse::Right, std::bind(clickRight, this));
    input.addRelease(sf::Mouse::Right, std::bind(releaseRight, this));

    input.addPress(sf::Mouse::Middle, std::bind(clickMiddle, this));
    input.addRelease(sf::Mouse::Middle, std::bind(releaseMiddle, this));

    input.scroll = std::bind(scroll, this, std::placeholders::_1);
}

void Game_State::loadSettings(Game_Settings settings)
{
    this->settings = settings;
    if (game) {
        game->loadSettings(settings);
    }
}

void Game_State::setHUDState(UI::State state)
{
    if (hud_states.contains(state)) {
        if (hud) {
            hud->exitState();
            drawables.pop_back();
        }
        hud = hud_states[state].get();
        hud->enterState();
        hud->grabElementActivity();
        drawables.push_back(hud);

        switch (state) {
            // state-specific operations
            default:
                break;
        }
    }
}

void Game_State::loadFunctions()
{
    // here, bind game functions to string identifiers
    Input_Accelerator* acc = &Game::core->systems.accelerator;
    string_to_function = {
        { "null", []() {} },

        // movement functions
        { "move up",    std::bind(&Input_Accelerator::startUp,      acc) },
        { "stop up",    std::bind(&Input_Accelerator::stopUp,       acc) },
        { "move left",  std::bind(&Input_Accelerator::startLeft,    acc) },
        { "stop left",  std::bind(&Input_Accelerator::stopLeft,     acc) },
        { "move down",  std::bind(&Input_Accelerator::startDown,    acc) },
        { "stop down",  std::bind(&Input_Accelerator::stopDown,     acc) },
        { "move right", std::bind(&Input_Accelerator::startRight,   acc) },
        { "stop right", std::bind(&Input_Accelerator::stopRight,    acc) },

        // debug
        { "regenerate", std::bind(newGame, this, data) }
    };
}

void Game_State::newGame(New_Game_Data data)
{
    game = std::make_unique<New_Game>(data);
    registration();
    setGameState(Game::NEW);
}

void Game_State::loadGame(std::filesystem::path load_path)
{
    game = std::make_unique<New_Game>(load_path);
    // re-registration is required for a new ecs_core
    registration();
    setGameState(Game::NEW);
}

void Game_State::newToPlay()
{
    // set HUD state

    Database_Commands dbc;
    loadCommands(dbc.read());

    windowResize();

    drawables.clear();
    drawables.push_back(&Game::core->systems.renderer);
    drawables.push_back(hud);
}

void Game_State::setGameState(Game::State state)
{
    game_state = state;
    switch (state) {
        // state-specific operations
        // also call setHUDState
        default:
            break;
    }
}

void Game_State::clear()
{
    game.reset();
    drawables.clear();
}

void Game_State::windowResize(const sf::Vector2u& w_size)
{
    this->w_size = w_size;
    UI::setView(w_size);
    for (auto& h : hud_states) {
        h.second->windowResize(w_size);
    }
    if (Game::core) {
        Game::core->systems.windowResize(w_size);
    }
}

void Game_State::windowResize()
{
    windowResize(w_size);
}
