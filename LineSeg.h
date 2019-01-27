#pragma once
#include "point.h"
#include <cmath>
namespace G2D
{
class LineSeg
{
  public:
    Point beg;
    Point end;

  public:
    LineSeg(Point bb = Point{}, Point ee = Point{}) : beg(bb), end(ee)
    {
    }
    double Length() const
    {
        return std::sqrt((beg.x - end.x) * (beg.x - end.x) + (beg.y - end.y) * (beg.y - end.y));
    }
    double Cross(const LineSeg &ls) const
    {
        auto v1 = end - beg;
        auto v2 = ls.end - ls.beg;
        return (v1.x*v2.y - v1.y*v2.x);
    }
};
} // namespace G2D