#pragma once

#include <magic_enum.hpp>

#include <iostream>
#include <cstdlib> // abort

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
        RADIONUCLIDES,
        HELIUM__3,
        PHOSPHATES,
        NITRATES,
        HYDROGEN,
        // secondary
        RESEARCH,
        ALLOYS,
        BASIC_GOODS,
        LUXURY_GOODS,
        ELECTRONICS,
        COUNT
    };

    inline const static std::string dash_code { "__" };
    inline const static std::string space_code { "_" };

    static std::string toString(Type t)
    {
        std::string s(magic_enum::enum_name(t));
        std::string::size_type n = 0;
        while ((n = s.find(dash_code, n)) != std::string::npos) {
            s.replace(n, dash_code.size(), "-");
        }
        n = 0;
        while ((n = s.find(space_code, n)) != std::string::npos) {
            s.replace(n, space_code.size(), " ");
        }
        return s;
    }

    static Type fromString(std::string s)
    {
        std::string::size_type n = 0;
        while ((n = s.find('-', n)) != std::string::npos) {
            s.replace(n, 1, dash_code);
        }
        n = 0;
        while ((n = s.find(' ', n)) != std::string::npos) {
            s.replace(n, 1, space_code);
        }
        Type t = magic_enum::enum_cast<Type>(s).value_or(COUNT);
        if (t == COUNT) {
            std::cout << "\n\ncritical error! failed to convert string " << s << " to resource type! aborting...\n\n";
            std::abort();
        }
        return t;
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
