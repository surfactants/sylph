#pragma once

#include <vector>

#include <game/component/body_info.hpp>

#include "database.hpp"

class Database_Body : public Database {
public:
    Database_Body() = default;

    std::vector<std::pair<Body_Info, Body_Info>> read()
    {
        std::transform(table.begin(), table.end(), table.begin(), toupper);
        selectTable("BODIES");

        std::vector<std::pair<Body_Info, Body_Info>> bodies;

        while (step()) {
            int col = 0;

            std::string subtype = toString(col++);
            std::string type = toString(col++);
            std::string description = toString(col++);
            float chance = toFloat(col++);

            Body_Info min = getBody(col);
            min.subtype = subtype;
            min.type = type;
            min.description = description;
            min.chance = chance;

            Body_Info max = getBody(col);
            max.subtype = subtype;
            max.type = type;
            max.description = description;
            max.chance = chance;

            bodies.push_back(std::make_pair(min, max));
        }
        return bodies;
    }

protected:
    Body_Info getBody(int& col)
    {
        Body_Info body;
        body.radius = toFloat(col++);
        body.temperature = toFloat(col++);
        body.light = toFloat(col++);
        int r = toInt(col++);
        int g = toInt(col++);
        int b = toInt(col++);
        body.color = sf::Color(r, g, b);
        return body;
    }
};
