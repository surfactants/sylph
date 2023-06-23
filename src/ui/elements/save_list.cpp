#include <ui/elements/save_list.hpp>

#include <chrono>
#include <filesystem>
#include <map>

#include <engine/util/time.hpp>

const std::string Save_List::path { "save/" };
const std::string Save_List::extension { ".db" };

namespace fs = std::filesystem;

Save_List::Save_List(const sf::Font& font
                   , std::function<void(fs::path)> chooseSave
                   , std::function<void()> discardSave
                   , bool save)
    : Toggle_Scroller(font)
    , chooseSave { chooseSave }
    , discardSave { discardSave }
    , save { save }
{
}

void Save_List::load()
{
    reset();
    rows.clear();
    filenames.clear();

    if (save) {
        filenames.push_back("new");
    }

    button_pos = sf::Vector2f(button_offset, button_offset);
    button_size = sf::Vector2f(192.f, 128.f);

    getFilenames();

    for (const auto& name : filenames) {
        Row r;

        // button
        r.button = Button(name, font, csize, Button::READY);
        r.button.setSize(button_size);
        r.button.setPosition(button_pos);

        // text
        r.text.setFont(font);
        //r.text.setString(name);
        r.text.setCharacterSize(csize);
        centerText(r.text);

        sf::Vector2f text_pos(button_pos + (button_size / 2.f));
        text_pos.x += button_size.x + button_offset;
        text_pos.x += (r.text.getGlobalBounds().left + r.text.getGlobalBounds().width) / 2.f;
        r.text.setPosition(text_pos);

        // data
        if (name == "new") {
            r.data = std::string();
        }
        else {
            r.data = path + name + extension;
        }

        rows.push_back(std::move(r));

        button_pos.y += button_size.y + button_offset;
    }

    setScrollable(button_pos.y);
}

void Save_List::getFilenames()
{
    std::map<time_t, std::string> sorter;
    for (const auto& entry : fs::directory_iterator(path)) {
        std::string ep = entry.path().filename().string();
        size_t ext = ep.find(extension);
        if (ext == std::string::npos) {
            continue;
        }
        ep.erase(ext, extension.size());
        auto time = to_time_t(entry.last_write_time());
        sorter[time] = ep;
        //auto e = entry.path().filename();
        //filenames.push_back(entry.path().filename().string());
    }

    for (auto it = sorter.rbegin(); it != sorter.rend(); it++) {
        filenames.push_back((*it).second);
    }
}

std::string Save_List::nextSaveName()
{
    std::string name = "save-";
    bool finding { true };
    unsigned int i = 0;
    do {
        std::string temp = name + std::to_string(i++);
        if (std::find(filenames.begin(), filenames.end(), temp) == filenames.end()) {
            finding = false;
            name = temp;
        }
    } while (finding);
    return name;
}

bool Save_List::clickLeft()
{
    if (!highlighted_row) {
        deactivate();
        discardSave();
        return true;
    }
    else if (highlighted_row != active_row) {
        if (active_row) {
            active_row->button.setToBase();
        }
        active_row = highlighted_row;
        active_row->button.setState(ACTIVE);
        activate();
        chooseSave(active_row->data);
        return true;
    }
    else if (state == READY) {
        if (active_row) {
            active_row->button.setState(READY);
            deactivate();
            discardSave();
            return true;
        }
    }
    return false;
}

bool Save_List::clickRight()
{
    deactivate();
    return true;
}
