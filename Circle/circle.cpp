#include <cmath>
#include <cstdio>
#include "circle.hpp"

Circle::Circle(): center(), radius(0.00) {}

Circle::Circle(Point init_c, double init_r): center(init_c), radius(init_r) {}

void Circle::move (double dx, double dy) {
    center.Point::move(dx, dy);
}

// Refer to https://stackoverflow.com/questions/67715025/how-to-calculate-the-area-of-two-circles-intersection
double Circle::intersectionArea(const Circle & otherCircle) {
    double intersec = 0.00;
    double dist = center.Point::distanceFrom(otherCircle.center);

    if (dist >= (radius + otherCircle.radius)) {
        intersec = 0.00;
        return intersec;
    }
    else if (dist <= fabs(radius - otherCircle.radius) && dist >= 0) {
        if (radius > otherCircle.radius) {
            intersec = M_PI * otherCircle.radius * otherCircle.radius;
            return intersec;
        }
        else {
            intersec = M_PI * radius * radius;
            return intersec;
        }
    }
    else {
        double A1 = 2 * acos((dist * dist + radius * radius - otherCircle.radius * otherCircle.radius) / (2 * dist * radius));
        double A2 = 2 * acos((dist * dist + otherCircle.radius * otherCircle.radius - radius * radius) / (2 * dist * otherCircle.radius));
        double s1 = 0.5 * radius * radius * sin(A1) +0.5 * otherCircle.radius * otherCircle.radius * sin(A2);
        double s2 = (A1) / 2 * radius * radius + (A2) / 2 * otherCircle.radius * otherCircle.radius;
        intersec = s2 -s1;
        return intersec;
    }
}