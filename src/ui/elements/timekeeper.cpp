#include <ui/elements/timekeeper.hpp>

#include <engine/resources/palette.hpp>

#include <engine/util/text.hpp>

#include <iostream>

Timekeeper::Timekeeper(const sf::Font& font, Localizer& localize)
{
    year_label.setFont(font);
    year_label.setFillColor(Palette::white);
    year_label.setCharacterSize(label_csize);

    std::string key = "YEAR";
    std::string loc = localize(key);
    year_label.setString(loc);
    localize.record(key, &year_label);
    centerText(year_label);

    year.setFont(font);
    year.setFillColor(Palette::white);
    year.setCharacterSize(csize);
    year.setString("1");
    centerText(year);

    month_label.setFont(font);
    month_label.setFillColor(Palette::white);
    month_label.setCharacterSize(label_csize);

    key = "MONTH";
    loc = localize(key);
    month_label.setString(loc);
    localize.record(key, &month_label);
    centerText(month_label);

    month.setFont(font);
    month.setFillColor(Palette::white);
    month.setCharacterSize(csize);
    month.setString("1");
    centerText(month);

    const sf::Vector2f year_size = textSize(year_label);
    const sf::Vector2f month_size = textSize(month_label);

    sf::Vector2f frame_size;
    frame_size.x = (padding * 4.f) + year_size.x + month_size.x;
    frame_size.y = (padding * 3.f) + year_size.y + month_size.y;
    frame.setSize(frame_size);

    frame.setFillColor(Palette::black);
    frame.setOutlineColor(Palette::white);
    frame.setOutlineThickness(outline);
}

void Timekeeper::setYear(const unsigned int year)
{
    std::cout << "\tyear set to " << year << '\n';
    this->year.setString(std::to_string(year));
    centerText(this->year);
}

void Timekeeper::setMonth(const unsigned int month)
{
    std::cout << "\tmonth set to " << month << '\n';
    this->month.setString(std::to_string(month));
    centerText(this->month);
}

void Timekeeper::setPosition(const sf::Vector2f& position)
{
    const sf::Vector2f year_size = textSize(year_label);
    const sf::Vector2f month_size = textSize(month_label);

    frame.setPosition(position);

    sf::Vector2f tpos = position + sf::Vector2f(padding, padding);
    tpos += year_size / 2.f;
    year_label.setPosition(tpos);

    sf::Vector2f bpos = tpos;
    bpos.y += (year_size.y / 2.f) + (padding * 3.f);
    year.setPosition(bpos);

    const float x_diff = (year_size.x / 2.f) + (padding * 2.f) + (month_size.x / 2.f);
    tpos.x += x_diff;
    bpos.x += x_diff;

    month_label.setPosition(tpos);
    month.setPosition(bpos);
}

void Timekeeper::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(frame, states);
    target.draw(year_label, states);
    target.draw(year, states);
    target.draw(month_label, states);
    target.draw(month, states);
}
