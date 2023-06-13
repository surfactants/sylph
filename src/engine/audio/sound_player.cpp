#include <engine/audio/sound_player.hpp>

#include <engine/database/database_sound.hpp>

Sound_Player::Sound_Player(Event_Bus& event_bus)
{
    event_bus.listen(Event::SOUND, std::bind(read, this, std::placeholders::_1));

    volume[Sound::UI] = 100.f;
    volume[Sound::GAME] = 100.f;

    Database_Sound db;
    context = db.read();
}

void Sound_Player::update()
{
    while (!sounds.empty() && sounds.front().getStatus() == sf::Sound::Stopped) {
        sounds.pop_front();
    }
}

void Sound_Player::setVolume(Sound::Source s, float vol)
{
    volume[s] = vol;
}

float Sound_Player::getVolume(Sound::Source s)
{
    return volume[s];
}

void Sound_Player::read(Event event)
{
    if (context[event.tag].ready()) {
        // look at other events and decide whether to add it (i.e. avoid cacophany)
        Sound& s = context[event.tag];
        sounds.push_back(sf::Sound(s.buffer));
        sounds.back().setVolume(volume[s.source]);
        sounds.back().play();
    }
}
