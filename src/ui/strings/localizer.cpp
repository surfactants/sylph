#include <ui/strings/localizer.hpp>

#include <engine/database/database_strings.hpp>
#include <engine/database/database_settings_general.hpp>

#include <iostream>

Localizer::Localizer()
{
    load();
}

void Localizer::load(std::string language)
{
    if (language.length() == 0) {
        // get language from settings
        Database_Settings_General dbsg;
        language = dbsg.activeLanguage();
    }
    this->language = language;
    Database_Strings db;
    db.read(strings, language);
}

void Localizer::record(std::string key, sf::Text* text)
{
    records[key].push_back(text);
}

void Localizer::recordPersistent(std::string key, sf::Text* text)
{
    persistent_records[key].push_back(text);
}

void Localizer::changeLanguage(std::string language)
{
    if (this->language != language) {
        load(language);
    }

    for (auto& p : persistent_records) {
        for (auto& r : p.second) {
            r->setString((*this)(p.first));
        }
    }

    for (auto& np : records) {
        for (auto& r : np.second) {
            if (r) {
                r->setString((*this)(np.first));
            }
        }
    }
}

void Localizer::erase(sf::Text* to_erase)
{
    for (auto& row : records) {
        for (auto it = row.second.begin(); it != row.second.end();) {
            if (*it == to_erase) {
                row.second.erase(it);
            }
            else {
                it++;
            }
        }
    }
}
