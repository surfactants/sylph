#pragma once

#include <SFML/Graphics/Text.hpp>

#include <map>
#include <string>
#include <vector>

#include <iostream>

class Localizer {
public:
    Localizer();

    std::string operator () (std::string key)
    {
        if (!strings.contains(key)) {
            // log this
            std::cout << "FAILED TO FIND LOCALIZED STRING FOR KEY '" << key << "'!\n";
        }
        return strings[key];
    }

    void record(std::string key, sf::Text* text);

    void recordPersistent(std::string key, sf::Text* text);

    void changeLanguage(std::string language);

    void erase(sf::Text* to_erase);

private:
    std::map<std::string, std::string> strings;
    std::map<std::string, std::vector<sf::Text*>> persistent_records;
    std::map<std::string, std::vector<sf::Text*>> records;

    void load(std::string language = "");

    std::string language;
};
