#include <game/core/save_game.hpp>

Save_Game::Save_Game(Component_Manager& components
        , Entity_Manager& entities
        , System_Manager& systems)
    : components { components }
    , entities { entities }
    , systems { systems }
{}
