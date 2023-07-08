#include <ui/elements/tabbed_panel.hpp>

Tabbed_Panel::Tab::Tab()
{
    target = [](){};
    deselect();
    frame.setFillColor(Palette::black);
    frame.setOutlineThickness(outline);
}

Tabbed_Panel::Tab::Tab(std::function<void()> target)
{
    target = target;
    deselect();
    frame.setFillColor(Palette::black);
    frame.setOutlineThickness(outline);
}

void Tabbed_Panel::Tab::select()
{
    state = SELECTED;
    frame.setOutlineColor(Palette::white);
}

void Tabbed_Panel::Tab::deselect()
{
    state = READY;
    frame.setOutlineColor(Palette::black);
}

bool Tabbed_Panel::Tab::update(const sf::Vector2i& mpos)
{
    bool cnt = contains(mpos);
    switch (state) {
        case READY:
            if (cnt) {
                state = HIGHLIGHTED;
            }
            break;
        case HIGHLIGHTED:
            if (!cnt) {
                state = READY;
            }
            break;
        default:
            break;
    }
    return cnt;
}

bool Tabbed_Panel::Tab::clickLeft()
{
    if (highlighted()) {
        target();
        select();
    }
    return highlighted();
}

bool Tabbed_Panel::update(const sf::Vector2i& mpos)
{
    if (moused && moused->update(mpos)) {
        return true;
    }
    else {
        moused = nullptr;
    }

    for (auto& tab : tabs) {
        if (tab.update(mpos)) {
            moused = &tab;
        }
    }
    if (current_panel->update(mpos)) {
        moused = current_panel;
    }
    return (moused);
}

void Tabbed_Panel::addPanel(std::shared_ptr<Panel> panel)
{
    size_t next_index = panels.size();

    // construct tab
    tabs.push_back(Tab());
    sf::Vector2f tab_pos(tab_frame.left, tab_frame.top);

    for (size_t i = 0; i < next_index; i++) {
        tab_pos.y += tab_size.y + (outline * 2.f);
    }
    tabs.back().setPosition(tab_pos);

    const float side { tab_frame.width - (outline * 2.f) };
    tabs.back().setSize(sf::Vector2f(side, side));

    panels.push_back(panel);

    if (!current_panel) {
        current_panel = panels.front().get();
        tabs.front().select();
        index = 0;
    }

    for (size_t i = 0; i <= next_index; i++) {
        tabs[i].target = std::bind(setTab, this, i);
    }
}

void Tabbed_Panel::setPosition(const sf::Vector2f& pos)
{
    tab_frame.left = pos.x;
    tab_frame.top = pos.y;
}

void Tabbed_Panel::setSize(const sf::Vector2f& size)
{
    tab_frame.width = size.x;
    tab_frame.height = size.y;

    tab_size.x = size.x - (outline * 2.f);
    tab_size.y = tab_size.x;
}

void Tabbed_Panel::setTab(const size_t index)
{
    // change tab rendering
    for (auto& tab : tabs) {
        tab.deselect();
    }
    tabs[index].select();

    // deactivate current panel
    current_panel->deactivate();

    current_panel = panels[index].get();
    this->index = index;
}

bool Tabbed_Panel::clickLeft()
{
    if (moused) {
        return moused->clickLeft();
    }
    return false;
}

bool Tabbed_Panel::releaseLeft()
{
    if (moused) {
        return moused->releaseLeft();
    }
    return false;
}

bool Tabbed_Panel::clickRight()
{
    return current_panel->clickRight();
}

bool Tabbed_Panel::releaseRight()
{
    return current_panel->releaseRight();
}

bool Tabbed_Panel::textEntered(const sf::Event& event)
{
    return current_panel->textEntered(event);
}

bool Tabbed_Panel::keyPressed(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Tab) {
        if (++index >= tabs.size()) {
            index = 0;
        }
        setTab(index);
        return true;
    }
    return current_panel->keyPressed(key);
}

void Tabbed_Panel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& tab : tabs) {
        target.draw(tab, states);
    }
    target.draw(*current_panel, states);
}
