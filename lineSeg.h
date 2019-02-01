#pragma once
#include "point.h"
#include <cmath>
#include <cassert>
#include <utility>
#include <algorithm>
#include <utility>
#include <type_traits>
#include <assert.h>

namespace G2D
{

template <typename T>
T vmin(T &&t)
{
    return std::forward<T>(t);
}

template <typename T0, typename T1, typename... Ts>
typename std::common_type<
    T0, T1, Ts...>::type
vmin(T0 &&val1, T1 &&val2, Ts &&... vs)
{
    if (val2 < val1)
        return vmin(val2, std::forward<Ts>(vs)...);
    else
        return vmin(val1, std::forward<Ts>(vs)...);
}

template <typename T>
T vmax(T &&t)
{
    return std::forward<T>(t);
}

template <typename T0, typename T1, typename... Ts>
typename std::common_type<
    T0, T1, Ts...>::type
vmax(T0 &&val1, T1 &&val2, Ts &&... vs)
{
    if (val2 < val1)
        return vmax(val2, std::forward<Ts>(vs)...);
    else
        return vmax(val1, std::forward<Ts>(vs)...);
}

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
        auto diff = end - beg;
        diff /= len;
        end = beg + diff;
    }
    LineSeg Norm() const
    {
        auto tmp = *this;
        tmp.NormSelf();
        return tmp;
    }
    void ScaleSelf(double rate)
    {
        auto diff = end - beg;
        diff *= rate;
        end = beg + diff;
    }
    LineSeg Scale(double rate) const
    {
        auto tmp = *this;
        tmp.ScaleSelf(rate);
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

    //beg到end的射线是否与线段ls相交
    bool isRadialIntersection(const LineSeg &ls) const
    {
        //todo:
        //如果场景有合理的值的范围，可以直接用边界的上下界，而不用下面的代码。

        //将线段延长至合理的范围
        auto diffx = end.x - beg.x;
        auto diffy = end.y - beg.y;

        decltype(end.x) maxs[] = {std::abs(vmax(end.x, beg.x, ls.end.x, ls.beg.x)) + 1.0, std::abs(vmax(end.y, beg.y, ls.end.y, ls.beg.y)) + 1.0};
        decltype(end.x) diffes[] = {diffx, diffy};
        decltype(end.x) base[] = {beg.x, beg.y};

        //选择x,y轴为参考，主要是防止diff值为0的时候
        int choose_dir = 0;
        if (std::abs(diffy) > std::abs(diffx))
        {
            choose_dir = 1;
        }
        assert(diffes[choose_dir] != 0);
        double sign = diffes[choose_dir] > 0 ? 1 : -1;
        auto target_value = maxs[choose_dir] * sign;
        double rate = (target_value - base[choose_dir]) / diffes[choose_dir];
        

        auto new_seg = this->Scale(rate);

        return new_seg.isIntersection(ls);
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