#include <menu/elements/scrollable.hpp>

#include <engine/resources/palette.hpp>

void Scrollable::setView(sf::Vector2f pos, sf::Vector2f size, sf::Vector2u window_size)
{
    this->size = size;
    sf::Vector2f wsize(window_size);
    float xs = size.x / wsize.x;
    float ys = size.y / wsize.y;

    float xp = pos.x / wsize.x;
    float yp = pos.y / wsize.y;

    view.setViewport(sf::FloatRect(xp, yp, xs, ys));
    view.setSize(sf::Vector2f(wsize.x * xs, wsize.y * ys));
    view.setCenter(size / 2.f);

    frame.left = pos.x;
    frame.top = pos.y;

    background.setFillColor(Palette::gray_dark);
}

sf::View Scrollable::getView() const
{
    return view;
}

void Scrollable::reset()
{
    scrollToTop();
    scrollbar.setSize(sf::Vector2f(scrollbar.getSize().x, 0.f));
    frame.height = 0.f;
}

void Scrollable::setScrollable(float max_height)
{
    scrollbar.setFillColor(Palette::white);
    scrollbar.setSize(sf::Vector2f(12.f, 12.f));

    scroll_x_pos = view.getSize().x - scrollbar.getSize().x;
    current_scroll = 0.f;

    frame = sf::FloatRect(sf::Vector2f(frame.left, frame.top), sf::Vector2f(size));

    max_scroll = max_height - size.y;
    if (max_scroll < 0.f) {
        max_scroll = 0.f;
    }

    resizeScrollbar();
    placeScrollbar();

    background.setSize(sf::Vector2f(size.x, max_scroll + size.y));
}

bool Scrollable::scroll(float delta, sf::Vector2f mpos) {
    bool c = contains(mpos);

    if (c) {
        delta *= -40.f;
        view.move(0.f, delta);
        current_scroll += delta;
        if(current_scroll < 0) {
            view.move(0.f, -current_scroll);
            current_scroll = 0;
        }
        else if(current_scroll > max_scroll) {
            view.move(0.f, -(current_scroll - max_scroll));
            current_scroll = max_scroll;
        }
        placeScrollbar();
    }

    return c;
}

void Scrollable::scrollToTop()
{
    view.setCenter(size / 2.f);
    current_scroll = 0.f;
    placeScrollbar();
}

void Scrollable::resizeScrollbar() {
    sf::Vector2f scroll_size(scrollbar.getSize().x, view.getSize().y);
    if(max_scroll > 0) {
        scroll_size.y *= (size.y / (max_scroll + size.y));
    }
    scrollbar.setSize(scroll_size);
    placeScrollbar();
}

void Scrollable::placeScrollbar() {
    sf::Vector2f pos(scroll_x_pos, current_scroll);
    pos.y += (size.y - scrollbar.getSize().y) * (current_scroll / max_scroll);
    if (max_scroll == 0.f) {
        pos.y = 0.f;
    }
    if(max_scroll > size.y) {
        //pos.y += (frame.height - scrollbar.getSize().y) * (current_scroll / max_scroll);
    }
    scrollbar.setPosition(pos);
}

sf::Vector2f Scrollable::getPosition()
{
    return sf::Vector2f(frame.left, frame.top);
}

sf::Vector2f Scrollable::getSize()
{
    return size;
}

sf::Vector2f Scrollable::scrollbarSize()
{
    return scrollbar.getSize();
}

void Scrollable::setBackground(sf::Color color)
{
    background.setFillColor(color);
}

void Scrollable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.setView(view);
    target.draw(background, states);
    target.draw(scrollbar, states);
}
