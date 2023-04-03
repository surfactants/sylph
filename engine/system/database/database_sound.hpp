#pragma once

#include <map>

#include <audio/sound.hpp>

#include "database.hpp"

class Database_Sound : protected Database {
public:
    Database_Sound();

    std::map<Event::Tag, Sound> getBuffers();
};
