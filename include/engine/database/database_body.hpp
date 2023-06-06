#pragma once

#include <cassert>
#include <sstream>
#include <vector>

#include <game/component/body_info.hpp>

#include "database.hpp"

using Resource_Chances = std::map<std::string, std::map<Resource::Type, float>>;
using Resource_Ranges = std::map<std::string, std::pair<Resource, Resource>>;

/// Database_Body ///
/// \brief reading is effected by the constructor
/// the various data are then publicly accessible:
/// - bodies (parameter ranges)
/// - descriptions
/// - resource_chances
/// - resource_ranges
///
class Database_Body : public Database {
public:
    Database_Body()
    {
        readBodies();
        readResources();
    }

    std::vector<std::pair<Body_Info, Body_Info>> bodies;
    std::map<std::string, std::string> descriptions;
    Resource_Chances resource_chances;
    Resource_Ranges resource_ranges;

    void readBodies()
    {
        std::transform(table.begin(), table.end(), table.begin(), toupper);
        selectTable("BODIES");

        while (step()) {
            int col = 0;

            std::string subtype = toString(col++);
            std::string type = toString(col++);
            float chance = toFloat(col++);

            Body_Info min = getBody(col);
            min.subtype = subtype;
            min.type = type;
            min.chance = chance;

            Body_Info max = getBody(col);
            max.subtype = subtype;
            max.type = type;
            max.chance = chance;

            bodies.push_back(std::make_pair(min, max));

            std::string description = toString(col++);
            descriptions[subtype] = description;
        }
    }

    void readResources()
    {
        std::transform(table.begin(), table.end(), table.begin(), toupper);
        selectTable("RESOURCES");

        std::map<int, std::string> columns;
        int n;
        for (int c = 1;; c++) {
            n = c;
            const char* name = sqlite3_column_name(statement, c);
            if (name) {
                columns[c] = std::string(name);
            }
            else {
                break;
            }
        }

        while (step()) {
            int col = 0;

            std::string body_type = toString(col);

            Resource min;
            Resource max;
            std::map<Resource::Type, float> chances;

            std::string column;

            while (++col < n) {
                column = columns[col];
                Resource::Type resource = Resource::fromString(column);

                std::stringstream chance_string;
                chance_string << toString(col); // "chance;min;max;"
                std::vector<float> split;
                std::string line;
                while (std::getline(chance_string, line, ';')) {
                    split.push_back(std::stof(line));
                }
                assert(split.size() == 3);
                float chance = split[0];
                float r_min = split[1];
                float r_max = split[2];

                chances[resource] = chance;

                min.set(resource, r_min);
                max.set(resource, r_max);
            }

            resource_chances[body_type] = chances;
            resource_ranges[body_type] = std::make_pair(min, max);
/*
            do {
                //auto col_ptr = std::string(sqlite3_column_name(statement, col));
                std::string resource_string = std::string(sqlite3_column_name(statement, col));
                Resource::Type resource = Resource::fromString(resource_string);

                std::stringstream chance_string;
                chance_string << toString(col++); // "chance;min;max;"
                std::vector<float> split;
                std::string line;
                while (std::getline(chance_string, line, ';')) {
                    split.push_back(std::stof(line));
                }
                assert(split.size() == 3);
                float chance = split[0];
                float r_min = split[1];
                float r_max = split[2];

                chances[resource] = chance;

                min.set(resource, r_min);
                max.set(resource, r_max);

                body_type = toString(col++);
            } while(column != "END");
            */
        }
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
