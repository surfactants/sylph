#include <game/system/renderer.hpp>

#include <cassert>

void Renderer::add(size_t layer, sf::Drawable* d)
{
    assert(layers.contains(layer) && "FAILED TO FIND VIEW LAYER IN RENDERER");
    layers[layer].drawables.push_back(d);
}

void Renderer::setLayer(size_t layer, sf::View* view)
{
    layers[layer].view = view;
}

void Renderer::nullCheck()
{
    for (auto& layer : layers) {
        for (auto d = layer.second.drawables.begin(); d != layer.second.drawables.end();) {
            if (*d == nullptr) {
                layer.second.drawables.erase(d);
            }
            else {
                d++;
            }
        }
    }
}

void Renderer::clear()
{
    layers.clear();
}

void Renderer::clearLayer(size_t layer)
{
    layers[layer].drawables.clear();
    layers.erase(layer);
}

void Renderer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& layer : layers) {
        target.setView(*layer.second.view);
        for (const auto& d : layer.second.drawables) {
            target.draw(*d, states);
        }
    }
}
