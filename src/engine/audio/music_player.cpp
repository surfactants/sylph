#include <engine/audio/music_player.hpp>

#include <filesystem>

#include <iostream>

Music_Player::Music_Player(Event_Bus& event_bus)
{
    event_bus.listen(Event::MAIN_MENU_ENTERED, std::bind(setTitle, this));
    event_bus.listen(Event::MAIN_MENU_EXITED, std::bind(setGame, this));
    setTitle();
    nextSong();
}

void Music_Player::setTitle()
{
    playlist.clear();
    playlist.push_back(filename("menu"));
    state = FADING_OUT;
}

void Music_Player::setGame()
{
    playlist.clear();
    std::string fname;
    int i = 0;
    while (std::filesystem::exists(fname = filename(i++))) {
        playlist.push_back(fname);
    }
    index = i;
    state = FADING_OUT;
}

std::string Music_Player::filename(int index)
{
    return std::string(root) + std::to_string(index) + std::string(extension);
}

std::string Music_Player::filename(std::string name)
{
    return std::string(root) + name + std::string(extension);
}

void Music_Player::nextSong()
{
    index++;
    if (index >= playlist.size()) {
        index = 0;
    }
    volume_tracker = 0.f;
    std::cout << "loading new song, " << playlist[index];
    music.openFromFile(playlist[index]);
    music.setVolume(volume_tracker);
    music.play();
    state = FADING_IN;
    fade_clock.restart();
}

void Music_Player::update()
{
    switch (state) {
        case FADING_OUT:
            if (fade_clock.getElapsedTime().asSeconds() >= fade_threshold) {
                fadeOut();
                fade_clock.restart();
            }
            break;
        case FADING_IN:
            if (fade_clock.getElapsedTime().asSeconds() >= fade_threshold) {
                fadeIn();
                fade_clock.restart();
            }
            break;
        case INTER:
            if (fade_clock.getElapsedTime().asSeconds() >= inter_threshold) {
                nextSong();
            }
            break;
        case PLAYING:
            if (music.getStatus() == sf::Music::Stopped) {
                state = INTER;
                fade_clock.restart();
            }
        default:
            break;
    }
}

void Music_Player::fadeOut()
{
    volume_tracker -= volume_offset;
    if (volume_tracker <= 0.f) {
        volume_tracker = 0.f;
        state = INTER;
    }
    music.setVolume(volume_tracker);
}

void Music_Player::fadeIn()
{
    volume_tracker += volume_offset;
    if (volume_tracker >= volume) {
        volume_tracker = volume;
        music.setVolume(volume);
        state = PLAYING;
    }
    music.setVolume(volume_tracker);
}

void Music_Player::setVolume(float vol)
{
    volume = vol;
    music.setVolume(vol);
}

float Music_Player::getVolume()
{
    return volume;
}
