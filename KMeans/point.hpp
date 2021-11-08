#pragma once

#include <limits.h>
#include <cfloat>

struct Point
{
    Point();
    Point(double x,double y);
    double distance(Point p);
    double x,y,minDist,cluster;
};