#include <menu/state/menu_save_game.hpp>

#include <game/core/save_game.hpp>
#include <game/state/game.hpp>

#include <engine/util/sfml_stream.hpp>

Menu_Save_Game::Menu_Save_Game()
    : save_list { Save_List(*font
                          , std::bind(chooseSave, this, std::placeholders::_1)
                          , std::bind(discardSave, this)
                          , true) }
{
    // textboxes, color pickers, buttons, checkboxes, sliders

    addNav("save", std::bind(confirmSave, this), Menu_Element::UNAVAILABLE);
    addNav("cancel", std::bind(setMenuState, Menu::PAUSE));

    setEscape(Main_State::QUIT);

    placeNav();

    sf::Vector2f pos = nav.front().getPosition();
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
    std::cout << "\nconfirm save...\n";
    if (dialog) {
        std::cout << "\tdialog!\n";
        active_save = std::filesystem::path(std::string(save_list.path + dialog->getString() + save_list.extension));
        cancelDialog();
    }
    else if (active_save.string().length() == 0) {
        std::cout << "\tempty save name!\n";
        // open save name decision dialog
        dialog = std::make_unique<Dialog>(*font, view.getSize());
        dialog->setTextbox("new save", true, save_list.nextSaveName());
        dialog->setConfirm(std::bind(confirmSave, this));
        dialog->setCancel(std::bind(cancelDialog, this));
        active_element = dialog.get();
        elements.push_back(dialog.get());
        return;
    }
    std::cout << "\t...\n";
    Save_Game save_game(Game::components, Game::entities, Game::systems, active_save);
    discardSave();
    // initiate game loading
    setMainState(Main_State::GAME);
}

void Menu_Save_Game::cancelDialog()
{
    moused_element = nullptr;
    active_element = nullptr;
    dialog = nullptr;
    elements.pop_back();
    //clearNullElements();
}

void Menu_Save_Game::deleteSave()
{
    discardSave();
}

void Menu_Save_Game::cancel()
{
    // reset values and return to main menu
    setMenuState(Menu::PAUSE);
}

void Menu_Save_Game::chooseSave(std::filesystem::path filename)
{
    active_save = filename;
    nav.front().setState(Button::READY);
}

void Menu_Save_Game::discardSave()
{
    nav.front().setState(Button::UNAVAILABLE);

}
