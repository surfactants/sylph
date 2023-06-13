#include <ui/elements/color_selector.hpp>

#include <engine/resources/palette.hpp>
#include <engine/util/text.hpp>

bool Color_Selector::initialized = false;

sf::VertexArray Color_Selector::colors;

sf::VertexArray Color_Selector::slider;

Color_Selector::Color_Selector()
{
    if (!initialized) {
        initialize();
    }
    prepare();
}

Color_Selector::Color_Selector(std::string title, const sf::Font& font)
{
    if (!initialized) {
        initialize();
    }
    prepare();
    label.setFont(font);
    label.setString(title);
    label.setFillColor(Palette::white);
    centerTextVertical(label);
}

void Color_Selector::initialize()
{
    initialized = true;
    colors.setPrimitiveType(sf::Points);
    colors.resize(256 * 256);

    slider.setPrimitiveType(sf::Quads);
    unsigned int ssize = 24;
    unsigned int v = 0;
    slider.resize(ssize);
    sf::Color slider_color = sf::Color(255, 0, 0);
    while (v < 2)
        slider[v++].color = slider_color;

    slider_color = sf::Color(255, 255, 0);
    while (v < 6) {
        slider[v++].color = slider_color;
    }

    slider_color = sf::Color(0, 255, 0);
    while (v < 10) {
        slider[v++].color = slider_color;
    }

    slider_color = sf::Color(0, 255, 255);
    while (v < 14) {
        slider[v++].color = slider_color;
    }

    slider_color = sf::Color(0, 0, 255);
    while (v < 18) {
        slider[v++].color = slider_color;
    }
    slider_color = sf::Color(255, 0, 255);
    while (v < 22) {
        slider[v++].color = slider_color;
    }

    slider_color = sf::Color(255, 0, 0);
    while (v < ssize) {
        slider[v++].color = slider_color;
    }

    setPosition(sf::Vector2f(16, 16));
}

void Color_Selector::prepare()
{
    selector = sf::RectangleShape(sf::Vector2f(8, 8));
    selector.setSize(sf::Vector2f(8, 8));
    selector.setOrigin(sf::Vector2f(selector.getSize().x / 2, selector.getSize().y / 2));
    selector.setOutlineThickness(1);
    selector.setOutlineColor(sf::Color(0, 0, 0));

    slider_handle = sf::RectangleShape(sf::Vector2f(slider[1].position.x - slider[0].position.x, 3));
    slider_handle.setPosition(slider[0].position);
    slider_handle.setOrigin(sf::Vector2f(0, slider_handle.getSize().y / 2));
    slider_handle.setFillColor(sf::Color(0, 0, 0, 0));
    slider_handle.setOutlineColor(sf::Color(250, 250, 250));
    slider_handle.setOutlineThickness(1);

    setHue();

    position = sf::Vector2f(0.f, 0.f);
    enactPosition();

    state = READY;
    base_state = READY;
}

void Color_Selector::reset()
{
    slider_handle.setPosition(slider[0].position);
    selector.setPosition(colors[0].position);
    setHue();
}

void Color_Selector::setPosition(sf::Vector2f pos)
{
    position = pos;
}
void Color_Selector::enactPosition()
{
    sf::Vector2f size = sf::Vector2f(256, 256);

    for (unsigned int y = 0; y < 256; y++) {
        for (unsigned int x = 0; x < 256; x++) {
            colors[x + y * 256].position.x = position.x + x;
            colors[x + y * 256].position.y = position.y + y;
        }
    }

    sf::Vector2f slider_pos = sf::Vector2f(position.x + size.x + 8, position.y);
    sf::Vector2f slider_size = sf::Vector2f(16, size.y / 6);

    unsigned int siter = 0;
    while (siter < slider.getVertexCount()) {
        slider[siter++].position = slider_pos;
        slider_pos.x += slider_size.x;
        slider[siter++].position = slider_pos;
        slider_pos.y += slider_size.y;
        slider[siter++].position = slider_pos;
        slider_pos.x -= slider_size.x;
        slider[siter++].position = slider_pos;
    }

    slider_handle.setPosition(slider[0].position);

    setHue();
}

void Color_Selector::setPreview(sf::Vector2f pos, sf::Vector2f size)
{
    preview.setPosition(pos);
    preview.setSize(size);

    pos.x += size.x + 32.f;
    pos.y += size.y / 2.f;
    label.setPosition(pos);
}

sf::Color Color_Selector::getColor()
{
    return preview.getFillColor();
}

bool Color_Selector::update(const sf::Vector2i& mpos)
{
    switch (state) {
        case READY:
            if (preview.getGlobalBounds().contains(mpos.x, mpos.y)) {
                moused = PREVIEW;
            }
            else {
                moused = NONE;
                return false;
            }
            break;
        case ACTIVE:
            if (selecting) {
                select(mpos);
            }
            else if (sliding) {
                slide(mpos);
            }
            else if (colors.getBounds().contains(mpos.x, mpos.y)) {
                moused = COLORS;
            }
            else if (slider.getBounds().contains(mpos.x, mpos.y)) {
                moused = SLIDER;
            }
            else if (preview.getGlobalBounds().contains(mpos.x, mpos.y)) {
                moused = PREVIEW;
            }
            else {
                moused = NONE;
                return false;
            }
            break;
        default:
            break;
    }
    return true;
}

void Color_Selector::clickLeft()
{
    switch (moused) {
        case COLORS:
            selecting = true;
            break;
        case SLIDER:
            sliding = true;
            break;
        case NONE:
            deactivate();
            break;
        default:
            break;
    }
}

void Color_Selector::releaseLeft()
{
    selecting = false;
    sliding = false;
    switch (moused) {
        case PREVIEW:
            if (active()) {
                deactivate();
            }
            else {
                activate();
            }
            break;
        default:
            break;
    }
}

void Color_Selector::activate()
{
    enactPosition();
    Element::activate();
    setState(ACTIVE);
}

void Color_Selector::deactivate()
{
    selecting = false;
    sliding = false;
    Element::deactivate();
}

void Color_Selector::clickRight()
{
}

void Color_Selector::releaseRight()
{
    if (moused == NONE) {
        deactivate();
    }
}

void Color_Selector::slide(sf::Vector2i mousePos)
{
    // this function is VERY heavy duty, presumably due to ::setHue(). try to find a way to optimize it.

    slider_handle.setPosition(sf::Vector2f(slider[0].position.x, mousePos.y));

    if (slider_handle.getPosition().y < slider[0].position.y) {
        slider_handle.setPosition(sf::Vector2f(slider_handle.getPosition().x, slider[0].position.y));
    }
    else if (slider_handle.getPosition().y > slider[23].position.y) {
        slider_handle.setPosition(sf::Vector2f(slider_handle.getPosition().x, slider[23].position.y));
    }

    setHue();

    sf::Vector2i local_pos(selector.getPosition() - colors[0].position);

    size_t index = local_pos.y * 256;
    index += local_pos.x;

    sf::Color selected_color = colors[index].color;
    preview.setFillColor(selected_color);
    selector.setFillColor(selected_color);
}

void Color_Selector::setHue()
{
    const double hue = (slider_handle.getPosition().y - slider[0].position.y) / (slider[23].position.y - slider[0].position.y);
    const int hp = hue * 6;
    for (unsigned int y = 0; y < 256; y++) {
        for (unsigned int x = 0; x < 256; x++) {
            const double s = x / 255.f;
            const double v = 1 - y / 255.f;

            const double f = hue * 6 - hp;
            const double p = v * (1 - s);
            const double q = v * (1 - s * f);
            const double t = v * (1 - s * (1 - f));

            switch (hp) {
                case 0:
                case 6:
                    colors[y * 256 + x].color = sf::Color(v * 255, t * 255, p * 255, alpha);
                    break;
                case 1:
                    colors[y * 256 + x].color = sf::Color(q * 255, v * 255, p * 255, alpha);
                    break;
                case 2:
                    colors[y * 256 + x].color = sf::Color(p * 255, v * 255, t * 255, alpha);
                    break;
                case 3:
                    colors[y * 256 + x].color = sf::Color(p * 255, q * 255, v * 255, alpha);
                    break;
                case 4:
                    colors[y * 256 + x].color = sf::Color(t * 255, p * 255, v * 255, alpha);
                    break;
                case 5:
                    colors[y * 256 + x].color = sf::Color(v * 255, p * 255, q * 255, alpha);
                    break;
            }
        }
    }

    select(sf::Vector2i(selector.getPosition().x, selector.getPosition().y));
}

void Color_Selector::select(sf::Vector2i mousePos)
{
    selector.setPosition(mousePos.x, mousePos.y);

    if (selector.getPosition().x < colors[0].position.x) {
        selector.setPosition(colors[0].position.x, selector.getPosition().y);
    }
    else if (selector.getPosition().x > colors[256 * 256 - 1].position.x) {
        selector.setPosition(colors[256 * 256 - 1].position.x, selector.getPosition().y);
    }

    if (selector.getPosition().y < colors[0].position.y) {
        selector.setPosition(selector.getPosition().x, colors[0].position.y);
    }
    else if (selector.getPosition().y > colors[256 * 256 - 1].position.y) {
        selector.setPosition(selector.getPosition().x, colors[256 * 256 - 1].position.y);
    }

    sf::Vector2i local_pos(selector.getPosition() - colors[0].position);

    size_t index = local_pos.y * 256;
    index += local_pos.x;

    sf::Color selected_color = colors[index].color;
    preview.setFillColor(selected_color);
    selector.setFillColor(selected_color);
}

void Color_Selector::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(preview, states);
    target.draw(label, states);
    if (active()) {
        target.draw(colors, states);
        target.draw(selector, states);
        target.draw(slider, states);
        target.draw(slider_handle, states);
    }
}
