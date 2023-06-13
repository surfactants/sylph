#include <ui/menu/menu_save_game.hpp>

#include <game/core/save_game.hpp>
#include <game/state/game.hpp>

Menu_Save_Game::Menu_Save_Game()
    : save_list { Save_List(*font
                          , std::bind(chooseSave, this, std::placeholders::_1)
                          , std::bind(discardSave, this)
                          , true) }
{
    // textboxes, color pickers, buttons, checkboxes, sliders

    addNav("save", std::bind(confirmSave, this), Element::UNAVAILABLE);
    addNav("cancel", std::bind(setUIState, UI::PAUSE));

    setEscape(Main_State::QUIT);

    placeNav();

    sf::Vector2f pos = nav.front()->getPosition();
    pos.x += 392.f;
    sf::Vector2f size(900.f, 900.f);
    save_list.setView(pos, size);
    save_list.setScrollable(size.y);

    elements.push_back(&save_list);
}

void Menu_Save_Game::enterState()
{
    save_list.load();
}

void Menu_Save_Game::exitState()
{
    save_list.scrollToTop();
}

void Menu_Save_Game::confirmSave()
{
    if (dialog) {
        active_save = std::filesystem::path(std::string(save_list.path + dialog->getString() + save_list.extension));
        cancelDialog();
    }
    else if (active_save.string().length() == 0) {
        // open save name decision dialog
        dialog = std::make_unique<Dialog>(font, view.getSize());
        dialog->setTextbox("new save", true, save_list.nextSaveName());
        active_save = std::filesystem::path(std::string(save_list.path + dialog->getString() + save_list.extension));
        dialog->setConfirm(std::bind(confirmSave, this));
        dialog->setCancel(std::bind(cancelDialog, this));
        active = dialog.get();
        elements.push_back(dialog.get());
        return;
    }
    Save_Game save_game(Game::core.get(), active_save);
    discardSave();
    // initiate game loading
    setMainState(Main_State::GAME);
}

void Menu_Save_Game::cancelDialog()
{
    moused = nullptr;
    active = nullptr;
    dialog = nullptr;
    clearNullElements();
}

void Menu_Save_Game::deleteSave()
{
    discardSave();
}

void Menu_Save_Game::cancel()
{
    // reset values and return to main menu
    setUIState(UI::PAUSE);
}

void Menu_Save_Game::chooseSave(std::filesystem::path filename)
{
    active_save = filename;
    nav.front()->setState(Button::READY);
}

void Menu_Save_Game::discardSave()
{
    nav.front()->setState(Button::UNAVAILABLE);

}
