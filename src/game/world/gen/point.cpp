#include <game/world/gen/point.hpp>

#include <cmath>

#if defined(_WIN64) || defined(_WIN32)
//    #define isnan(x) _isnan(x)
#endif

using namespace std;

const double Point::Inf = std::numeric_limits<double>::infinity();

Point::Point_Compare Point::compare = Point::Point_Compare();

Point::Point(double x, double y)
    : x { x }
    , y { y }
{
}

Point::Point(const Point& point)
    : x(point.x)
    , y(point.y)
{
}

sf::Vector2f Point::sfv()
{
    return sf::Vector2f(x, y);
}

Point& Point::operator-=(const Point& p)
{
    x -= p.x;
    y -= p.y;
    return *this;
}

Point& Point::operator+=(const Point& p)
{
    x += p.x;
    y += p.y;
    return *this;
}

Point& Point::operator*=(double value)
{
    x *= value;
    y *= value;
    return *this;
}

Point& Point::operator/=(double value)
{
    x /= value;
    y /= value;
    return *this;
}

double Point::operator[](int i)
{
    if (i == 0)
        return x;
    else
        return y;
}

void Point::setX(double x)
{
    this->x = x;
}

void Point::setY(double y)
{
    this->y = y;
}

bool Point::isVertical()
{
    return (y == Inf && !isnan(x) && x != Inf);
}

bool Point::isHorizontal()
{
    return (x == Inf && !isnan(y) && y != Inf);
}

bool Point::isValid()
{
    if (x == Inf && y == Inf)
        return false;
    return (!isnan(x) && !isnan(y));
}

Point Point::normalized()
{
    return (*this) / this->norm();
}

void Point::normalize()
{
    double n = norm();
    x /= n;
    y /= n;
}

double Point::norm()
{
    return sqrt(x * x + y * y);
}

double Point::norm2()
{
    return x * x + y * y;
}

Point Point::getRotated90CW()
{
    return Point(y, -x);
}

Point Point::getRotated90CCW()
{
    return Point(-y, x);
}

double dotProduct(const Point& p1, const Point& p2)
{
    return p1.x * p2.x + p1.y * p2.y;
}

double crossProduct(const Point& p1, const Point& p2)
{
    return p1.x * p2.y - p1.y * p2.x;
}

Point operator+(const Point& p1, const Point& p2)
{
    return Point(p1.x + p2.x, p1.y + p2.y);
}

Point operator-(const Point& p1, const Point& p2)
{
    return Point(p1.x - p2.x, p1.y - p2.y);
}

Point operator/(const Point& p1, const Point& p2)
{
    return Point(p1.x / p2.x, p1.y / p2.y);
}

Point operator*(const Point& p, double value)
{
    return Point(p.x * value, p.y * value);
}

Point operator*(double value, const Point& p)
{
    return Point(p.x * value, p.y * value);
}

Point operator/(const Point& p, double value)
{
    return Point(p.x / value, p.y / value);
}

Point operator-(const Point& p)
{
    return Point(-p.x, -p.y);
}

bool operator==(const Point& p0, const Point& p1)
{
    return ((int)p0.x == (int)p1.x && (int)p0.y == (int)p1.y);
}

std::ostream& operator<<(std::ostream& stream, const Point& p)
{
    stream << "(" << p.x << "," << p.y << ")";
    return stream;
}

std::vector<Point>& operator<<(std::vector<Point>& v, const Point& p)
{
    v.push_back(p);
    return v;
}

bool isLeftTurn(const Point& p1, const Point& p2, const Point& p3)
{
    return (crossProduct(p2 - p1, p3 - p2) > 0.0);
}

bool isRightTurn(const Point& p1, const Point& p2, const Point& p3)
{
    return (crossProduct(p2 - p1, p3 - p2) < 0.0);
}

bool equal(const Point& p1, const Point& p2, double EPSILON)
{
    return (fabs(p1.x - p2.x) < EPSILON && fabs(p1.y - p2.y) < EPSILON);
}

bool equal(double v1, double v2, double EPSILON)
{
    return fabs(v1 - v2) < EPSILON;
}
