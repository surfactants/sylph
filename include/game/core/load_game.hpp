#pragma once

#include <sqlite3.h>

#include <filesystem>
#include <sstream>
#include <string>

#include <engine/database/database.hpp>

#include <game/core/component_serializer.hpp>
#include <game/core/ecs_core.hpp>

class Load_Game : public Database{
public:
    Load_Game(ECS_Core* core, std::filesystem::path file);

private:
    ECS_Core* core;

    Component_Serializer serializer;

    void readInfo();
    void readEntities();
    void readComponents();

    void bodyInfo();
    void civData();
    void collisionRect();
    void entityData();
    void hierarchy();
    void polygonTile();
    void resource();
    void tile();
    void transform();

    void passCivs();
    void passTiles();

    template <typename T>
    void vectorize(std::vector<sf::Vector2<T>>& v_all, const std::string& read)
    {
        std::istringstream rstream { read };
        std::string entry;
        while (std::getline(rstream, entry, ';')) {
            sf::Vector2<T> v;
            auto it = entry.find(',');
            v.x = std::stof(entry.substr(0, it));
            v.y = std::stof(entry.substr(it + 1));
            v_all.push_back(v);
        }
    }

    void vectorize(std::vector<Entity>& v_all, const std::string read)
    {
        std::istringstream rstream { read };
        std::string entry;
        while (std::getline(rstream, entry, ';')) {
            v_all.push_back(std::stoi(entry));
        }
    }

    void readColor(int& col, sf::Color& color, bool trans = false)
    {
        int r = toInt(col++);
        int g = toInt(col++);
        int b = toInt(col++);
        int a = 255;
        if (trans) {
            a = toInt(col++);
        }
        color = sf::Color(r, g, b, a);
    }
};
