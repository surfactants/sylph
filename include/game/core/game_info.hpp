#pragma once

#include <game/core/entity.hpp>

struct Game_Info {
    Entity player;
    std::string player_name;
    unsigned int year { 0 };
    unsigned int minutes_played { 0 };

    std::string timePlayed()
    {
        unsigned int hours_played = minutes_played / 60;
        unsigned int minutes_left = minutes_played % 60;
        std::string time = std::to_string(hours_played) + ":";
        if (minutes_left < 10) {
            time += "0";
        }
        time += std::to_string(minutes_played);
        return time;
    }
};
