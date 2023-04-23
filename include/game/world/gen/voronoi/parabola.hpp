#pragma once

#include <SFML/System/Vector2.hpp>

#include <vector>

#include "point.hpp"

namespace Voronoi {

int intersectionPointsNum(const Point& f1, const Point& f2);

std::vector<Point> findIntersections(const Point& f1, const Point& f2, double directrix);

}
