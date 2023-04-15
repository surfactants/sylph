#include <engine/audio/audio.hpp>

#include <engine/database/database_volume.hpp>

Audio::Audio(Event_Bus& event_bus)
    : music { event_bus }
    , sound { event_bus }
{
    load();
}

void Audio::update()
{
    music.update();
    sound.update();
}

void Audio::setMusicVolume(float vol)
{
    music.setVolume(vol);
}

float Audio::getMusicVolume()
{
    return music.getVolume();
}

void Audio::setSoundVolume(Sound::Source s, float vol)
{
    sound.setVolume(s, vol);
}

float Audio::getSoundVolume(Sound::Source s)
{
    return sound.getVolume(s);
}

void Audio::loadDefaults()
{
    load(true);
}

void Audio::load(bool default_vol)
{
    Database_Volume db(default_vol);
    for (auto& v : db.getVolume()) {
        if (v.first == Sound::MUSIC) {
            music.setVolume(v.second);
        }
        else {
            sound.setVolume(v.first, v.second);
        }
    }
}

void Audio::saveToDatabase()
{
    Database_Volume db;
    std::map<Sound::Source, float> volume;
    volume[Sound::MUSIC] = music.getVolume();
    volume[Sound::GAME] = sound.getVolume(Sound::GAME);
    volume[Sound::UI] = sound.getVolume(Sound::UI);
    db.write(volume);
}
