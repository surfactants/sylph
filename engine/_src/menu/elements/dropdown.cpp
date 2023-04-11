#include <menu/elements/dropdown.hpp>

Dropdown::Option::Option(std::string label, sf::Font& font, unsigned int csize, State base)
    : Button(label, font, csize, base)
{}

void Dropdown::Option::update(const sf::Vector2i& mpos)
{
    bool cnt = Menu_Element::contains(mpos);

    if (cnt) {
        switch (state) {
            case READY:
                if (cnt) {
                    setState(HIGHLIGHTED);
                }
                break;
            case HIGHLIGHTED:
                if (!cnt) {
                    setState(READY);
                }
                break;
            default:
                break;
        }
    }

    return cnt;
}

Dropdown::Dropdown()
{}

void Dropdown::load(std::vector<std::pair<std::string, T>> data, sf::Font& font, size_t current)
{
    for (const auto& d : data) {
        options.push_back(Option(d.first, font, csize, READY));
        options.back().data = d.second;
    }

    options[current].setState(ACTIVE);
}

void Dropdown::update(const sf::Vector2i& mpos)
{
    bool cnt = contains(mpos);

    switch (state) {
        case READY:
            if (cnt) {
                setState(HIGHLIGHTED);
            }
            break;
        case HIGHLIGHTED:
            if (!cnt) {
                setState(READY);
            }
            break;
        case ACTIVE:
            cnt = activeUpdate(mpos);
            break;
        default:
            break;
    }

    return cnt;
}

bool Dropdown::activeUpdate(sf::Vector2i mpos)
{
    mpos = option_frame.translateGlobalPos(mpos);
    bool cnt = option_frame.contains(mpos);
    moused_option = nullptr;
    if (cnt) {
        for (auto& o : options) {
            if (o.update(mpos)) {
                moused_option = &o;
            }
        }
    }
    return cnt;
}

void Dropdown::clickLeft()
{
    if (moused_option) {
        active_option->setToBase();
        active_option = moused_option;
        active_option->setState(ACTIVE);
    }
}

void Dropdown::releaseLeft()
{}

void Dropdown::reset()
{
    if (moused_option) {
        moused_option->setToBase();
        moused_option = nullptr;
    }
}

void Dropdown::deactivate()
{
    Menu_Element::deactivate();
    reset();
}

void Dropdown::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    switch (state) {
        case ACTIVE:
            target.setView(option_frame.getView());
            for (const auto& o : options) {
                target.draw(o, states);
            }
            break;
        case READY:
            target.draw(frame, states);
            target.draw(label, states);
            break;
        default:
            break;
    }
}
