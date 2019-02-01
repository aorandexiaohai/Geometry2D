#pragma once
#include "point.h"
#include "lineSeg.h"
namespace G2D{
    //简单多边形:凹或者凸多边形
    class Polygon{
    public:
        std::vector<Point> pts;
    private:
        //边界是不是在多边形内部
        bool isPointIn(const Point& pt)const
        {
            //当射线穿越多边形边界的次数为偶数时，所有第偶数次（包括最后一次）穿越都是穿出，因此所有第奇数次（包括第一次）穿越为穿入，由此可推断点在多边形外部。
            //当射线穿越多边形边界的次数为奇数时，所有第奇数次（包括第一次和最后一次）穿越都是穿出，由此可推断点在多边形内部。

            //特殊情况:
            //如果点P在边P1P2上，则直接判定点P在多边形内；
            //如果从P发出的射线正好穿过P1或者P2，那么这个交点会被算作2次（因为在处理以P1或P2为端点的其它边时可能已经计算过这个点了），对这种情况的处理原则是：如果P的y坐标与P1、P2中较小的y坐标相同，则忽略这个交点
            //如果从P发出的射线与P1P2平行，则忽略这条边
            int size = pts.size();
            int count = 0;
            //构造向右边的射线:水平射线
            LineSeg ls(pt, Point(pt.x+1, pt.y));
            for(int i=0; i<size; i++)
            {
                auto& prev = pts[i];
                auto& next = pts[(i+1) % size];
                LineSeg cur(prev, next);
                if(cur.isOn(pt)) return true;
                else if((prev.x >= pt.x && prev.y==pt.y) || (next.x >= pt.x && next.y==pt.y))
                {
                    if(vmin(prev.y, next.y) != pt.y)
                    {
                        count++;
                    }
                }
                else if(ls.isIntersection(cur))
                {
                    continue;
                }
                else 
                {
                    if(ls.isRadialIntersection(cur))
                        count++;
                }
            }
            return count%2==1;
        }
    };
}