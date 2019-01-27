#pragma once
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
    bool operator==(const Point &pt) const
    {
        return (!(*this < pt)) && (!(pt < *this));
    }
};
} // namespace G2D