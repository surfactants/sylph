#include <ui/menu/menu_load_game.hpp>

std::function<void(std::filesystem::path)> Menu_Load_Game::loadGame;

Menu_Load_Game::Menu_Load_Game()
    : save_list { Save_List(*font
                          , std::bind(chooseSave, this, std::placeholders::_1)
                          , std::bind(discardSave, this)) }
{
    addNav("BUTTON_CONFIRM", std::bind(confirm, this), Element::UNAVAILABLE);
    addNav("BUTTON_CANCEL", std::bind(&UI::escape, this));

    setEscape(Main_State::QUIT);

    placeNav();

    sf::Vector2f pos = nav.front()->getPosition();
    pos.x += 392.f;
    sf::Vector2f size(900.f, 900.f);
    save_list.setView(pos, size);
    save_list.setScrollable(size.y);

    elements.push_back(&save_list);
}

void Menu_Load_Game::enterState()
{
    save_list.load();
}

void Menu_Load_Game::exitState()
{
    save_list.scrollToTop();
}

void Menu_Load_Game::chooseSave(std::filesystem::path filename)
{
    active_save = filename;
    nav.front()->setState(Button::READY);
}

void Menu_Load_Game::discardSave()
{
    nav.front()->setState(Button::UNAVAILABLE);
}

void Menu_Load_Game::deleteSave()
{
    discardSave();
}

void Menu_Load_Game::cancel()
{
    // reset values and return to main menu
    setUIState(UI::PAUSE);
}

void Menu_Load_Game::cancelDialog()
{
    controller.moused = nullptr;
    controller.active = nullptr;
    dialog = nullptr;
    elements.pop_back();
    //clearNullElements();
}

void Menu_Load_Game::confirm()
{
    if (dialog) {
        cancelDialog();
    }
    else if (active_save.string().length() != 0) {
        // open confirmation dialog
        dialog = std::make_unique<Dialog>(font, view.getSize());
        dialog->setText("confirm");
        dialog->setConfirm(std::bind(confirm, this));
        dialog->setCancel(std::bind(cancelDialog, this));
        controller.setActive(dialog.get());
        elements.push_back(dialog.get());
        return;
    }
    clearGame();
    loadGame(active_save);
    discardSave();
    // initiate game loading
    setMainState(Main_State::GAME);
}
