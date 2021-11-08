
#include <limits.h>
#include <cfloat>
#include "point.hpp"

Point::Point():x(0.0),
           y(0.0),
           minDist(DBL_MAX),
           cluster(-1)
    {
        
    }
Point::Point(double x,double y):x(x),
      y(y),
      minDist(DBL_MAX),
      cluster(-1)
    {
        
    }
double Point::distance(Point p)
{
    return (((p.x-x)*(p.x-x)) + ((p.y-y)*(p.y-y)));
}

