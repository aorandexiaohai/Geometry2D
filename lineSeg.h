#pragma once
#include "point.h"
#include <cmath>
#include <cassert>
#include <utility>
#include <algorithm>

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
        return (v1.x * v2.y - v1.y * v2.x);
    }
    double dot(const LineSeg &ls) const
    {
        auto v1 = end - beg;
        auto v2 = ls.end - ls.beg;
        return (v1.x * v2.x + v1.y * v2.y);
    }
    void NormSelf()
    {
        auto len = this->length();
        auto diff = end-beg;
        diff /= len;
        end = beg + diff;
    }
    LineSeg Norm()const
    {
        auto tmp = *this;
        tmp.NormSelf();
        return tmp;
    }
    //连续线段p0p1 p1p2
    //this代表:p0p1
    //ls代表:p1p2
    //p1p2相对于p0p1,在p1处是否左转
    //结果:
    //1:左转
    //0:共线
    //-1:右转
    int rotateLeft(const LineSeg &ls) const
    {
        //必须相等
        assert(this->end == ls.beg);

        auto indicator = this->cross(ls);
        if (indicator < 0)
            return -1;
        else if (indicator > 0)
            return 1;
        return 0;
    }
    bool isIntersection(const LineSeg &ls) const
    {
        return SEGMENTS_INTERSECT(this->beg, this->end, ls.beg, ls.end);
    }

  private:
    static double DIRECTION(const Point &pi, const Point &pj, const Point &pk)
    {
        //Cross(pipk, pipj)
        return LineSeg(pi, pk).cross(LineSeg(pi, pj));
    }
    static bool ON_SEGMENT(const Point &pi, const Point &pj, const Point &pk)
    {
        auto xi = pi.x;
        auto xj = pj.x;
        auto xk = pk.x;

        auto yi = pi.y;
        auto yj = pj.y;
        auto yk = pk.y;

        if (std::min(xi, xj) <= xk && xk <= std::max(xi, xj) && std::min(yi, yj) <= yk && yk <= std::max(yi, yj))
            return true;
        return false;
    }
    static bool SEGMENTS_INTERSECT(const Point &p1, const Point &p2, const Point &p3, const Point &p4)
    {
        auto d1 = DIRECTION(p3, p4, p1);
        auto d2 = DIRECTION(p3, p4, p2);
        auto d3 = DIRECTION(p1, p2, p3);
        auto d4 = DIRECTION(p1, p2, p4);
        if (d1 * d2 < 0 && d3 * d4 < 0)
            return true;
        else if (d1 == 0 && ON_SEGMENT(p3, p4, p1))
            return true;
        else if (d2 == 0 && ON_SEGMENT(p3, p4, p2))
            return true;
        else if (d3 == 0 && ON_SEGMENT(p1, p2, p3))
            return true;
        else if (d4 == 0 && ON_SEGMENT(p1, p2, p4))
            return true;
        return false;
    }
};
} // namespace G2D