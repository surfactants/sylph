#pragma once

#include <filesystem>
#include <vector>

#include "toggle_scroller.hpp"

class Save_List : public Toggle_Scroller<std::filesystem::path> {
public:
    Save_List(const sf::Font& font
            , std::function<void(std::filesystem::path)> chooseSave
            , std::function<void()> discardSave
            , bool save = false);

    void load();

    // replicate logic from Toggle_Scroller
    virtual bool clickLeft() override;

    virtual bool clickRight() override;

    const static std::string path;
    const static std::string extension;

    std::string nextSaveName();

private:
    std::vector<std::string> filenames;

    std::function<void(std::filesystem::path)> chooseSave;
    std::function<void()> discardSave;

    void getFilenames();

    const bool save;
};
