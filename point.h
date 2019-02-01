#pragma once
#include <vector>
#define PI 3.1415926535897932
#define DEGREE PI / 180.0
#define DEG *(DEGREE)
namespace G2D
{
class Point
{
  public:
    double x = 0.0;
    double y = 0.0;
    Point(double xx = 0, double yy = 0)
    {
        x = xx;
        y = yy;
    }
    Point operator+(const Point &other) const
    {
        return {x + other.x, y + other.y};
    }
    Point operator-(const Point &other) const
    {
        return {x - other.x, y - other.y};
    }
    bool operator<(const Point &pt) const
    {
        if (x < pt.x)
            return true;
        else if (x == pt.x)
            return y < pt.y;
        return false;
    }
    Point operator*(double rate) const
    {
        return {x * rate, y * rate};
    }
    Point &operator*=(double rate)
    {
        x *= rate;
        y *= rate;
        return *this;
    }
    Point &operator/=(double rate)
    {
        return (*this)*=(1.0/rate);
    }
    Point operator/(double rate) const
    {
        return (*this) * (1.0 / rate);
    }
    bool operator==(const Point &pt) const
    {
        return (!(*this < pt)) && (!(pt < *this));
    }
    /*测试任意三点是否都共线*/
  public:
    //n^2log(n) 算法复杂度
    static bool onLine(const std::vector<Point> &pts);
    //角度pjpipk的大小，[2, PI)
    static double polarAngle(const Point &pi, const Point &pj, const Point &pk);
};
} // namespace G2D