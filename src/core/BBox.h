/* =====================================================================================
 *
 * Filename:  BBox.h
 *
 * Description:  Defines a struct to represent an axis-aligned bounding box.
 *
 * =====================================================================================
 */
#ifndef BBOX_H
#define BBOX_H

#include "Point.h"
#include <iostream>
#include <limits>

/**
 * @struct BBox
 * @brief Represents an axis-aligned bounding box defined by minimum and maximum coordinates.
 */
struct BBox {
    int minX = 0; //left edge
    int minY = 0; //top edge
    int maxX = 0; //right edge
    int maxY = 0; //bottom edge
    Point center = {0,0}; //center
    int width = 0;
    int height = 0;

    BBox() = default;
    /**
     * @brief Constructs a BBox from two Points.
     * @param min The Point defining the top-left corner.
     * @param max The Point defining the bottom-right corner.
     */
    BBox(Point&& min, Point&& max): minX(min.x), minY(min.y), maxX(max.x), maxY(max.y) {
        center = {minX + (maxX - minX) / 2, minY + (maxY - minY) / 2};
        width = maxX - minX + 1;
        height = maxY - minY + 1;
    }

    /**
     * @brief Template function that computes the minimal bounding box of input points.
     * @param points The containter of points
     */
    template <typename Container>
    void compute(const Container& points) {
        if (points.empty()) {
            // Handle the case of an empty container
            minX = minY = maxX = maxY = 0;
            width = height = 0;
            center = {0, 0};
            return;
        }

        // Initialize bounds to opposite extremes
        minX = std::numeric_limits<int>::max();
        minY = std::numeric_limits<int>::max();
        maxX = std::numeric_limits<int>::min();
        maxY = std::numeric_limits<int>::min();

        for (const Point& p : points) {
            if (p.x < minX) minX = p.x;
            if (p.x > maxX) maxX = p.x;
            if (p.y < minY) minY = p.y;
            if (p.y > maxY) maxY = p.y;
        }

        width = maxX - minX;
        height = maxY - minY;
        center = {minX + width / 2, minY + height / 2};
    }
};

/**
 * @brief Overloads the stream insertion operator for easy printing of BBox objects.
 * @param os The output stream.
 * @param bbox The BBox object to print.
 * @return A reference to the output stream.
 */
inline std::ostream& operator<<(std::ostream& os, const BBox& bbox) {
    os << "BBox: (" << bbox.minX << ", " << bbox.minY << "), (" << bbox.maxX << ", " << bbox.maxY << ")\n";
    return os;
}

#endif // BBOX_H
