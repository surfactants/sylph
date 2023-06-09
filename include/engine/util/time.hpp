#pragma once

#include <chrono>
#include <filesystem>

template <typename T>
time_t to_time_t(T t)
{
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>(t - T::clock::now() + system_clock::now());
    return system_clock::to_time_t(sctp);
}
