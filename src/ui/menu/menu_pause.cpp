#include <ui/menu/menu_pause.hpp>

#include <engine/event/event_bus.hpp>

Menu_Pause::Menu_Pause()
{
    addNav("BUTTON_CONTINUE", std::bind(&UI::escape, this));
    addNav("BUTTON_SAVE", std::bind(setUIState, UI::SAVE_GAME));
    addNav("BUTTON_LOAD", std::bind(setUIState, UI::LOAD_GAME));
    addNav("BUTTON_SETTINGS", std::bind(setUIState, UI::SETTINGS));
    auto main_menu =
        [&]() {
            setUIState(UI::TITLE);
            clearGame();
            Event_Bus::publish(Event::MAIN_MENU_ENTERED);
        };
    addNav("BUTTON_QUIT_TO_TITLE", main_menu);
    addNav("BUTTON_QUIT_TO_DESKTOP", std::bind(setMainState, Main_State::QUIT));

    setEscape(Main_State::GAME);

    placeNav();
}
