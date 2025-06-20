#include "BBox.h"
#include <iostream>

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
}

std::ostream& operator<<(std::ostream& os, const BBox& bbox) {
    os << "BBox: (" << bbox.minX << ", " << bbox.minY << "), (" << bbox.maxX << ", " << bbox.maxY << ")\n";
    return os;
}
