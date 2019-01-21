//c++11
#include <cmath>

const double INF = 1e200;
const double EP = 1e-10;
const double PI = 3.1415926535897932;
using namespace std;
class Point
{
  public:
    double x = 0.0;
    double y = 0.0;

  public:
    Point(double xx = 0.0, double yy = 0.0)
    {
        x = xx;
        y = yy;
    }
    double length() const
    {
        return sqrt(x * x + y * y);
    }
    bool operator==(const Point &pt) const
    {
        return std::abs(x - pt.x) < EP && std::abs(y - pt.y) < EP;
    }
    static double distance(const Point &pt1, const Point &pt2)
    {
        double dx = pt1.x - pt2.x;
        double dy = pt1.y - pt2.y;
        return std::sqrt(dx * dx + dy * dy);
    }
    Point operator-(const Point &pt) const
    {
        return {x - pt.x, y - pt.y};
    }
    Point operator+(const Point &pt) const
    {
        return {x + pt.x, y + pt.y};
    }
    //以this为中心,旋转alpha(弧度),
    Point rotate(double alpha, const Point &p)
    {
        auto &org = *this;
        auto new_ord = p - org;
        auto x = new_ord.x;
        auto y = new_ord.y;
        Point new_p(x * cos(alpha) - y * sin(alpha), y * cos(alpha) + x * sin(alpha));
        return new_p + org;
    }
};

/*向量*/
class Vec
{
  public:
    Point pt;

  public:
    Vec(const Point &p = {})
    {
        pt = p;
    }
    double cross(const Vec &vec) const
    {
        auto &p1 = this->pt;
        auto &p2 = vec.pt;
        return p1.x * p2.y - p1.y * p2.x;
    }
    double dot(const Vec &vec) const
    {
        auto &p1 = this->pt;
        auto &p2 = vec.pt;
        return p1.x * p2.x - p1.y * p2.y;
    }
    double angle(const Vec &vec) const
    {
        auto l1 = this->pt.length();
        auto l2 = vec.pt.length();
        if (l1 < EP || l2 < EP)
            return 0.0;
        auto dt = this->dot(vec);
        return std::acos(dt / l1 / l2);
    };
};

class LineSeg
{
  public:
    Point s;
    Point e;

  public:
    LineSeg(const Point &ss = {}, const Point &ee = {})
    {
        s = ss;
        e = ee;
    }
    bool isOnLine(const Point &pt) const
    {
        LineSeg ls1(s, pt);
        LineSeg ls2(pt, e);
        auto l1 = ls1.length();
        auto l2 = ls2.length();
        if (l1 <= EP || l2 <= EP)
            return true;
        auto cro = ls1.toVec().cross(ls2.toVec());
        return std::asin(cro / l1 / l2) < EP;
    }
    double length() const
    {
        return Point::distance(s, e);
    }
    Vec toVec() const
    {
        return Point{
            e.x - s.x,
            e.y - s.y,
        };
    }
    Point perpendicularPoint(const Point& pt) const;
};
/*
    线是特殊的线段
*/
class Line : public LineSeg
{
};
