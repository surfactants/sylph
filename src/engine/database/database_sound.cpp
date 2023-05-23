#include <engine/database/database_sound.hpp>

#include <magic_enum.hpp>

Database_Sound::Database_Sound()
{
    selectTable("SOUNDS");
}

std::map<Event::Tag, Sound> Database_Sound::getBuffers()
{
    std::map<Event::Tag, Sound> buffers;

    int row = 0;

    while (step()) {
        int col = 0;

        using magic_enum::enum_cast;

        // load tag and source using magic_enum
        Event::Tag tag = enum_cast<Event::Tag>(toString(col++)).value_or(Event::Tag::NONE);
        Sound::Source src = enum_cast<Sound::Source>(toString(col++)).value_or(Sound::Source::UI);
        float threshold = toFloat(col++);

        // todo: toBlob()

        // load buffer
        sqlite3_blob* blob;
        sqlite3_blob_open(db, "main", "SOUNDS", "DATA", ++row, 0, &blob);
        int bsize = sqlite3_blob_bytes(blob);
        char* buffer = new char[bsize];
        sqlite3_blob_read(blob, buffer, bsize, 0);
        sf::SoundBuffer sound;
        sound.loadFromMemory(buffer, bsize);
        delete[] buffer;
        sqlite3_blob_close(blob);

        buffers[tag] = Sound(sound, threshold, src);
    }

    return buffers;
}
