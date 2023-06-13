#pragma once

#include <filesystem>

#include <ui/elements/save_list.hpp>

#include "menu.hpp"

class Menu_Load_Game : public Menu {
public:
    Menu_Load_Game();

    void confirmLoad();
    void deleteSave();
    void cancel();

    virtual void enterState() override;
    virtual void exitState() override;

    void chooseSave(std::filesystem::path filename);
    void discardSave();

    static std::function<void(std::filesystem::path)> loadGame;

private:
    Save_List save_list;

    std::filesystem::path active_save;

    void cancelDialog();
};
