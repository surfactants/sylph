#include <engine/database/database_volume.hpp>

#include <magic_enum.hpp>

Database_Volume::Database_Volume(bool default_vol)
{
    std::string table = "VOLUME";
    if (default_vol) {
        table += "_DEFAULT";
    }
    selectTable(table);
}

std::map<Sound::Source, float> Database_Volume::getVolume()
{
    std::map<Sound::Source, float> volume;

    while (step()) {
        int col = 0;

        using magic_enum::enum_cast;

        Sound::Source src = enum_cast<Sound::Source>(toString(col++)).value_or(Sound::Source::UI);
        float v = sqlite3_column_double(statement, col++);

        volume[src] = v;
    }

    return volume;
}

void Database_Volume::write(std::map<Sound::Source, float> volume)
{
    for (const auto& v : volume) {
        std::string sql = "UPDATE VOLUME SET VALUE = ? WHERE ID = ?";
        sqlite3_prepare_v2(db, sql.c_str(), -1, &statement, NULL);
        sqlite3_bind_int(statement, 1, v.second);
        std::string s(magic_enum::enum_name(v.first));
        sqlite3_bind_text(statement, 2, s.c_str(), s.size(), NULL);
        sqlite3_step(statement);
        finalize();
    }
}
