#include "BBox.h"
#include <iostream>

BBox::BBox(Point&& min, Point&& max) : minX(min.x), minY(min.y), maxX(max.x), maxY(max.y) {
    center = {minX + (maxX - minX) / 2, minY + (maxY - minY) / 2};
    width = maxX - minX + 1;
    height = maxY - minY + 1;
}

void BBox::compute(const std::set<Point>& points) {

    if (points.empty())
        return;

    const auto& first = *points.begin();
    minX = maxX = first.x;
    minY = maxY = first.y;

    for (const auto& point : points) {
        minX = std::min(minX, point.x);
        maxX = std::max(maxX, point.x);
        minY = std::min(minY, point.y);
        maxY = std::max(maxY, point.y);
    }

    center = {minX + (maxX - minX) / 2, minY + (maxY - minY) / 2};
    width = maxX - minX + 1;
    height = maxY - minY + 1;
}

std::ostream& operator<<(std::ostream& os, const BBox& bbox) {
    os << "BBox: (" << bbox.minX << ", " << bbox.minY << "), (" << bbox.maxX << ", " << bbox.maxY << ")\n";
    return os;
}
