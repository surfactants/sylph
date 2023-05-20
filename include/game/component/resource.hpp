#pragma once

#include <magic_enum.hpp>

struct Resource {
public:
    enum Type {
        // primary
        ENERGY,
        FOOD,
        TEXTILES,
        WATER,
        AMMONIA,
        SILICATES,
        METALS,
        RARE_METALS,
        HYDROCARBONS,
        RADIONUCLES,
        HELIUM3,
        PHOSPHATES,
        NITRATES,
        HYDROGEN,
        // secondary
        RESEARCH,
        ALLOYS,
        BASIC_GOODS,
        LUXURY_GOODS,
        ELECTRONICS
    };

    static std::string toString(Type t)
    {
        return std::string(magic_enum::enum_name(t));
    }

    float operator [] (Type t)
    {
        if (values.contains(t)) {
            return values[t];
        }

        return 0.f;
    }

    void set(Type t, float val)
    {
        values[t] = val;
    }

    void remove(Type t)
    {
        values.erase(t);
    }

    std::map<Type, float> values;
};
