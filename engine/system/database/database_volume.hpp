#pragma once

#include <map>

#include <audio/sound.hpp>

#include "database.hpp"

class Database_Volume : protected Database {
public:
    Database_Volume(bool default_vol = false);

    std::map<Sound::Source, float> getVolume();

    void write(std::map<Sound::Source, float> volume);
};
