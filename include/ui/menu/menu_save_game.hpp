#pragma once

#include <filesystem>

#include <ui/elements/save_list.hpp>

#include "menu.hpp"

class Menu_Save_Game : public Menu {
public:
    Menu_Save_Game();

    void confirmSave();
    void deleteSave();
    void cancel();

    virtual void enterState() override;
    virtual void exitState() override;

    void chooseSave(std::filesystem::path filename);
    void discardSave();

private:
    Save_List save_list;
    // add confirmation dialog for overwriting

    void cancelDialog();

    std::filesystem::path active_save;
};
