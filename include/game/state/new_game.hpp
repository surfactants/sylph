#pragma once

#include <atomic>
#include <filesystem>
#include <thread>

#include <game/data/new_game_data.hpp>

#include "game.hpp"

class New_Game : public Game {
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
    std::atomic_flag thread_done { ATOMIC_FLAG_INIT };
    std::thread thread;

    New_Game_Data data;

    void createWorld();
    void generateSystem(Entity system);
    void createCivilizations();

    void load(std::filesystem::path load_path);

    std::vector<std::function<void()>> tasks;
    size_t task_index { 0 };
};
