#pragma once

#include <memory>

#include "button.hpp"
#include "panel.hpp"

class Tabbed_Panel : public Element {
private:
    class Tab : public Button {
    public:
        Tab();
        Tab(std::function<void()> target);

        void select();

        void deselect();

        virtual bool update(const sf::Vector2i& mpos) override;

        virtual bool clickLeft() override;
    };

public:
    virtual bool update(const sf::Vector2i& mpos) override;

    void addPanel(std::shared_ptr<Panel> panel);

    virtual void setPosition(const sf::Vector2f& pos) override;
    void setSize(const sf::Vector2f& size);

    virtual bool clickLeft() override;
    virtual bool releaseLeft() override;

    virtual bool clickRight() override;
    virtual bool releaseRight() override;

    virtual bool textEntered(const sf::Event& event) override;
    virtual bool keyPressed(sf::Keyboard::Key key) override;

    void setTab(const size_t index);

protected:
    std::vector<std::shared_ptr<Panel>> panels;

    std::vector<Tab> tabs;

    Panel* current_panel { nullptr };
    Element* moused { nullptr };
    Element* active { nullptr };
    size_t index { 0 };

    sf::FloatRect tab_frame;
    sf::Vector2f tab_size;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
