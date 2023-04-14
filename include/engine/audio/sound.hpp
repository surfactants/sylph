#pragma once

#include <SFML/Audio/SoundBuffer.hpp>

#include <SFML/System/Clock.hpp>

#include <engine/event/event.hpp>

/////////////////////////////////////////////////////////////
/// \brief Stores sound buffers and retains time context
///
class Sound {
public:
    enum Source {
        UI,
        GAME,
        MUSIC
    };

    Sound() = default;
    Sound(sf::SoundBuffer buffer, float threshold, Source source)
        : buffer { buffer }
        , source { source }
        , threshold { threshold }
    {}

    bool ready()
    {
        if (clock.getElapsedTime().asSeconds() >= threshold) {
            clock.restart();
            return true;
        }
        return false;
    }

    sf::SoundBuffer buffer;
    Source source;

private:
    sf::Clock clock;
    float threshold;
};
