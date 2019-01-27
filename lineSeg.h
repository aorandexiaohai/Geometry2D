#pragma once
#include "point.h"
#include <cmath>
#include <cassert>
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
    double length() const
    {
        return std::sqrt((beg.x - end.x) * (beg.x - end.x) + (beg.y - end.y) * (beg.y - end.y));
    }
    double cross(const LineSeg &ls) const
    {
        auto v1 = end - beg;
        auto v2 = ls.end - ls.beg;
        return (v1.x*v2.y - v1.y*v2.x);
    }
    //连续线段p0p1 p1p2
    //this代表:p0p1
    //ls代表:p1p2
    //p1p2相对于p0p1,在p1处是否左转
    //结果:
    //1:左转
    //0:共线
    //-1:右转
    int rotateLeft(const LineSeg& ls) const
    {
        //必须相等
        assert(this->end == ls.beg);

        auto indicator = this->cross(ls);
        if(indicator < 0) return -1;
        else if (indicator>0) return 1;
        return 0;

    }
};
} // namespace G2D