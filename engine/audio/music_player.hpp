#pragma once

#include <SFML/Audio.hpp>

#include <string>
#include <vector>

#include <system/event/event_bus.hpp>

class Music_Player {
public:
    Music_Player(Event_Bus& event_bus);

    void update();

    void setVolume(float vol);
    float getVolume();

    enum State {
        PAUSED,
        PLAYING,
        FADING_OUT,
        FADING_IN,
        INTER
    };

    State state { INTER };

private:
    float volume { 100.f };
    float volume_tracker;

    std::vector<std::string> playlist;
    size_t index { 0 };

    constexpr static std::string_view root = "soundtrack/";
    constexpr static std::string_view extension = ".wav";

    std::string filename(int index);
    std::string filename(std::string name);

    void setTitle();
    void setGame();

    sf::Music music;

    sf::Clock fade_clock;
    constexpr static float fade_threshold { 0.075f };
    constexpr static float inter_threshold { 1.5f };

    constexpr static float volume_offset { 1.5f };

    void nextSong();
    void fadeOut();
    void fadeIn();
};
