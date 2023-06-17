#include <ui/menu/menu_pause.hpp>

#include <engine/event/event_bus.hpp>

Menu_Pause::Menu_Pause()
{
    addNav("resume", std::bind(&UI::escape, this));
    addNav("save game", std::bind(setUIState, UI::SAVE_GAME));
    addNav("load game", std::bind(setUIState, UI::LOAD_GAME));
    addNav("settings", std::bind(setUIState, UI::SETTINGS));
    auto main_menu =
        [&]() {
            setUIState(UI::TITLE);
            clearGame();
            Event_Bus::publish(Event::MAIN_MENU_ENTERED);
        };
    addNav("quit to title", main_menu);
    addNav("quit to desktop", std::bind(setMainState, Main_State::QUIT));

    setEscape(Main_State::GAME);

    placeNav();
}
