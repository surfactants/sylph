#pragma once

#include <atomic>
#include <thread>

#include <game/data/new_game_data.hpp>

#include "game.hpp"

class New_Game : public Game {
public:
    New_Game(New_Game_Data data);

    virtual void update(float delta_time, const sf::Vector2f& mpos) override;

    virtual void loadSettings(Game_Settings settings) override;

    static std::function<void()> newToPlay;

private:
    std::atomic_flag thread_done { ATOMIC_FLAG_INIT };
    std::thread thread;

    New_Game_Data data;

    void createWorld();
    void createPlayer();

    std::vector<std::function<void()>> tasks;
    size_t task_index { 0 };
};
