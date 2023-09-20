#include <ui/ui_controller.hpp>

UI_Controller::UI_Controller(std::vector<Element*>& elements)
    : elements { elements }
{}

void UI_Controller::update(const sf::Vector2i& mpos)
{
    if (active) {
        if (active->update(mpos)) {
            moused = active;
            // still active, truncate
            return;
        }
    }

    if (moused) {
        if (!moused->update(mpos)) {
            moused = nullptr;
        }
        else {
            // still moused, truncate
            return;
        }
    }

    // check all elements
    for (auto& element : elements) {
        if (element->update(mpos)) {
            moused = element;
            break;
        }
    }
}

void UI_Controller::setActive(Element* element)
{
    if (active && active != element) {
        active->deactivate();
    }
    active = element;
}

void UI_Controller::unsetActive(Element* element)
{
    active = nullptr;
}
