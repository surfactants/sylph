#include <system/database/database_commands.hpp>

Database_Commands::Database_Commands()
{
    selectTable("COMMANDS");
}

std::vector<Command> Database_Commands::read()
{
    std::vector<Command> pkg;



    return pkg;
}

void Database_Commands::write(std::vector<Command> pkg)
{
    for (const auto& c : pkg) {
    }
}
