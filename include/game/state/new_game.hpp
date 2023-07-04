#pragma once

#include <atomic>
#include <filesystem>
#include <thread>

#include <engine/util/async_loader.hpp>

#include <game/data/new_game_data.hpp>

#include "game.hpp"

class New_Game : public Game, public Async_Loader {
public:
    New_Game(New_Game_Data data);
    New_Game(std::filesystem::path load_path);

    virtual void update(const float delta_time) override;

    virtual void loadSettings(Game_Settings settings) override;

    static std::function<void()> newToPlay;

    virtual void clickLeft() override;
    virtual void releaseLeft() override;
    virtual void clickRight() override;
    virtual void releaseRight() override;
    virtual void clickMiddle() override;
    virtual void releaseMiddle() override;

private:
    New_Game_Data data;

    void createWorld();
    void generateSystem(Entity system);
    void createCivilizations();
    void finalPrep();

    void load(std::filesystem::path load_path);
};
