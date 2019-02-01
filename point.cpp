#include "point.h"
#include "lineSeg.h"
#include <cmath>

using namespace G2D;
static double polarAngle(const Point& pi, const Point& pj, const Point& pk)
{
    LineSeg vij(pi, pj);
    LineSeg vik(pi, pk);
    vij.NormSelf();
    vik.NormSelf();
    auto cv = vij.cross(vik);
    auto dv = vij.dot(vik);
    if(cv >= 0 )
        return std::acos(dv);
    else
        return 2 * PI - std::acos(dv);
}