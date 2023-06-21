#include <ui/elements/resource_panel.hpp>

#include <engine/math/primordial.hpp>

#include <engine/resources/palette.hpp>
#include <engine/resources/texture_manager.hpp>

#include <engine/util/sfml_stream.hpp>

const sf::Vector2f Resource_Panel::icon_size = sf::Vector2f(32.f, 32.f);
const sf::Vector2f Resource_Panel::padding = sf::Vector2f(16.f, 16.f);

Resource_Panel::Resource_Panel()
    : texture { *Texture_Manager::get("RESOURCE_ICONS") }
{
    frame.setSize(sf::Vector2f(256.f, 1080.f));
}

void Resource_Panel::read(const Resource& resource)
{
    // std::map<Resource::Type, float>
    for (const auto& v : resource.values) {
        cells_by_type[v.first]->text.setString(std::to_string(v.second));
    }
}

void Resource_Panel::initialize(const Resource& resource, const sf::Font& font)
{
    // avoid static initialization order fiasco by defining color here
    frame.setFillColor(Palette::black);
    frame.setOutlineColor(Palette::white);
    frame.setOutlineThickness(2.f);

    cells.clear();
    cells_by_type.clear();
    const int secondary = static_cast<int>(Resource::SECONDARY) + 1;
    for (const auto& v : resource.values) {
        Cell c;
        c.sprite.setTexture(texture);
        sf::IntRect trect;
        trect.width = icon_size.x;
        trect.height = icon_size.y;

        int t = static_cast<int>(v.first);

        sf::Vector2i index(t, 0);

        if (t >= secondary) {
            index.x -= secondary;
            index.y++;
        }

        trect.left = index.x * roundFloat(icon_size.x);
        trect.top = index.y * roundFloat(icon_size.y);

        c.sprite.setTextureRect(trect);

        c.text.setFont(font);
        c.text.setString(std::to_string(v.second));
        c.text.setFillColor(Palette::white);
        cells.push_back(std::make_unique<Cell>(c));
        cells_by_type[v.first] = cells.back().get();
    }
}

void Resource_Panel::setPosition(sf::Vector2f position)
{
    frame.setPosition(position);
    position += padding;
    for (auto& cell : cells) {
        cell->sprite.setPosition(position);
        sf::Vector2f tpos = position;
        tpos.x += icon_size.x + padding.x;
        cell->text.setPosition(tpos);
        std::cout << tpos << '\n';
        position.y += icon_size.y + padding.y;
    }
}

void Resource_Panel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(frame, states);
    for (const auto& cell : cells) {
        target.draw(cell->sprite, states);
        target.draw(cell->text, states);
    }
}
