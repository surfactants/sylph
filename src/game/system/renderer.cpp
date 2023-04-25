#include <game/system/renderer.hpp>

void Renderer::add(sf::Drawable* d)
{
    drawables.push_back(d);
}

void Renderer::nullCheck()
{
    for (auto it = drawables.begin(); it != drawables.end();) {
        if (*it == nullptr) {
            drawables.erase(it);
        }
        else {
            it++;
        }
    }
}

void Renderer::clear()
{
    drawables.clear();
}

void Renderer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto& d : drawables) {
        target.draw(*d, states);
    }
}
