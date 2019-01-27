#pragma once
namespace G2D
{
class Point
{
  private:
    double x = 0.0;
    double y = 0.0;
  Point(double xx, double yy){
      x = xx;
      y = yy;
  }
};
} // namespace G2D