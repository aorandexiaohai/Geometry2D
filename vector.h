#pragma once
#include "LineSeg.h"
namespace G2D{
    class Vector: public LineSeg
    {
        public:
            Vector(Point ee = Point{}):LineSeg(Point{}, ee)
            {
            }
    };
}