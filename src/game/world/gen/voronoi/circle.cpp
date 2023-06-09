#include <game/world/gen/voronoi/circle.hpp>

#include <cmath>

namespace Voronoi {

bool findCircleCenter(const Point& p1, const Point& p2, const Point& p3, Point& center)
{

    // get normalized vectors
    Point u1 = (p1 - p2).normalized(), u2 = (p3 - p2).normalized();

    double cross = crossProduct(u1, u2);

    // check if vectors are collinear
    if (fabs(cross) < CIRCLE_CENTER_EPSILON) {
        return false;
    }

    // get cental points
    Point pc1 = 0.5 * (p1 + p2), pc2 = 0.5 * (p2 + p3);

    // get free components
    double b1 = dotProduct(u1, pc1), b2 = dotProduct(u2, pc2);

    // calculate the center of a circle
    center.x = (b1 * u2.y - b2 * u1.y) / cross;
    center.y = (u1.x * b2 - u2.x * b1) / cross;

    return true;
}

}
