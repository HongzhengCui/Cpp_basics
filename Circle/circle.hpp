#include <iostream>
#include <cstdio>
#include "point.hpp"

class Circle {
private:
    Point center;
    const double radius;
public:
    Circle();
    Circle(Point init_c, double init_r);
    void move (double dx, double dy);
    double intersectionArea(const Circle & otherCircle);
};