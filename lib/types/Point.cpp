#include "calgopp/types/Point.h"

#include <cmath>
#include <numeric>

namespace calgopp::types {

Point& Point::operator+=(const Point& other)
{
    this->x += other.x;
    this->y += other.y;
    return *this;
}

Point& Point::operator-=(const Point& other)
{
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}

bool operator==(const Point& lhs, const Point& rhs)
{
    return math::abs(lhs.x - rhs.x) < std::numeric_limits<double>::epsilon() && lhs.y == rhs.y;
}

bool operator==(const Point&& lhs, const Point&& rhs)
{
    return math::abs(lhs.x - rhs.x) < std::numeric_limits<double>::epsilon() && lhs.y == rhs.y;
}

bool operator!=(const Point& lhs, const Point& rhs)
{
    return !(lhs == rhs);
}

bool operator!=(const Point&& lhs, const Point&& rhs)
{
    return !(lhs == rhs);
}

Point operator+(const Point& lhs, const Point& rhs)
{
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

Point operator-(const Point& lhs, const Point& rhs)
{
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

} // namespace calgopp::types
