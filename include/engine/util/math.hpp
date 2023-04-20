#pragma once

template <typename T>
int sign(T val)
{
    return (T(0) < val) - (val < T(0));
}

inline int roundFloat(float f)
{
    return static_cast<int>(f + (sign(f) / 2.f));
}
