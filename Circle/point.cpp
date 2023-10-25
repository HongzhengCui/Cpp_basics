#include "point.hpp"
#include <cmath>

Point::Point() : x(0.0), y(0.0) {}

void Point::move(double dx, double dy) {
    x += dx;
    y += dy;
}

double Point::distanceFrom(const Point& p) {
    double dx = x - p.x;
    double dy = y - p.y;
    return std::sqrt(dx * dx + dy * dy);
}