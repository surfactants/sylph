#include <engine/database/database_sound.hpp>

#include <magic_enum.hpp>

Database_Sound::Database_Sound()
{
    selectTable("SOUNDS");
}

std::map<Event::Tag, Sound> Database_Sound::read()
{
    using magic_enum::enum_cast;

    std::map<Event::Tag, Sound> sounds;

    int row = 1;

    while (step()) {
        int col = 0;

        // load tag and source using magic_enum
        Event::Tag tag = enum_cast<Event::Tag>(toString(col++)).value_or(Event::Tag::NONE);
        Sound::Source src = enum_cast<Sound::Source>(toString(col++)).value_or(Sound::Source::UI);
        float threshold = toFloat(col++);

        // load buffer
        Blob blob = toBlob(row++);
        sf::SoundBuffer sound_buffer;
        sound_buffer.loadFromMemory(blob.buffer.get(), blob.length);
        sounds[tag] = Sound(sound_buffer, threshold, src);
    }

    return sounds;
}
