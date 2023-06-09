#pragma once

#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <vector>

namespace Voronoi {

constexpr double POINT_EPSILON { 1.0e-6 };

class Point {

    struct Point_Compare {
        bool operator()(const Point& p1, const Point& p2)
        {
            return (p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y));
        }
    };

public:
    double x, y;

    const static double Inf;
    static Point_Compare compare;

    Point(double x = 0.0, double y = 0.0);
    Point(const Point& point);

    friend double dotProduct(const Point& p1, const Point& p2);
    friend double crossProduct(const Point& p1, const Point& p2);

    friend Point operator+(const Point& p1, const Point& p2);
    friend Point operator-(const Point& p1, const Point& p2);
    friend Point operator/(const Point& p1, const Point& p2);
    friend Point operator*(const Point& p, double value);
    friend Point operator*(double value, const Point& p);
    friend Point operator/(const Point& p, double value);
    friend Point operator-(const Point& p);

    friend std::ostream& operator<<(std::ostream& stream, const Point& p);
    friend std::vector<Point>& operator<<(std::vector<Point>& v, const Point& p);

    Point& operator-=(const Point& p);
    Point& operator+=(const Point& p);
    Point& operator*=(double value);
    Point& operator/=(double value);

    Point normalized();
    void normalize();
    double norm();
    double norm2();

    Point getRotated90CW();
    Point getRotated90CCW();

    static bool isLeftTurn(const Point& p1, const Point& p2, const Point& p3);
    static bool isRightTurn(const Point& p1, const Point& p2, const Point& p3);

    double operator[](int i);

    void setX(double x);
    void setY(double y);

    bool isVertical();
    bool isHorizontal();
    bool isValid();

    sf::Vector2f sfv();
};

double dotProduct(const Point& p1, const Point& p2);
double crossProduct(const Point& p1, const Point& p2);

bool equal(const Point& p1, const Point& p2, double EPSILON = POINT_EPSILON);
bool equal(double v1, double v2, double EPSILON = POINT_EPSILON);

bool operator==(const Point& p0, const Point& p1);

}
