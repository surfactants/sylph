#include <system/main_state/main_state.hpp>

std::function<void(Main_State::State)> Main_State::setState;

Main_State::Main_State()
{
    /*
    sf::Vector2f size(1920.f, 1080.f);
    float xs = 1.f;
    float ys = 1.f;

    float xp = 0.f;
    float yp = 0.f;

    view.setViewport(sf::FloatRect(xp, yp, xs, ys));
    view.setSize(size);
    view.setCenter(size / 2.f);
    */
    sf::Vector2f pos(0.f, 0.f);
    sf::Vector2f size(1920.f, 1080.f);
    sf::Vector2f wsize(1920.f, 1080.f);
    float xs = size.x / wsize.x;
    float ys = size.y / wsize.y;

    float xp = pos.x / wsize.x;
    float yp = pos.y / wsize.y;

    view.setViewport(sf::FloatRect(xp, yp, xs, ys));
    view.setSize(sf::Vector2f(wsize.x * xs, wsize.y * ys));
    view.setCenter(size / 2.f);
}

void Main_State::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.setView(view);
    for (const auto& drawable : drawables) {
        target.draw(*drawable, states);
    }
}
