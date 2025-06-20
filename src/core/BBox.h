#ifndef BBOX_H
#define BBOX_H

#include "Point.h"
#include <set>
#include <ostream>

struct BBox {
    int minX = 0;
    int minY = 0;
    int maxX = 0;
    int maxY = 0;

    BBox() {}
    BBox(Point&& min, Point&& max) : minX(min.x), minY(min.y), maxX(max.x), maxY(max.y) {}

    void compute(const std::set<Point>& points);
};

std::ostream& operator<< (std::ostream& os, const BBox& bbox);

#endif // BBOX_H
