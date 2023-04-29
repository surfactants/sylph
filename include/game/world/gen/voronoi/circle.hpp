#pragma once

#include "point.hpp"

namespace Voronoi {

constexpr double CIRCLE_CENTER_EPSILON { 1.0e-7 };

bool findCircleCenter(const Point& p1, const Point& p2, const Point& p3, Point& center);

}
