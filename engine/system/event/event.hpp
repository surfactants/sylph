#pragma once

struct Event {
    enum Type {
        SOUND,
        MAIN_MENU_ENTERED,
        MAIN_MENU_EXITED
    };

    enum class Tag {
        BUTTON_PRESSED,
        BUTTON_TRIGGERED,
        SLIDER_MOVED,
        NONE
    };

    Type type;

    Tag tag;

    Event(Type type, Tag tag = Tag::NONE)
        : type { type }
        , tag { tag }
        {}
};
