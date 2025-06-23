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
#include <set>
#include <ostream>

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

    BBox() {}
    /**
     * @brief Constructs a BBox from two Points.
     * @param min The Point defining the top-left corner.
     * @param max The Point defining the bottom-right corner.
     */
    BBox(Point&& min, Point&& max) : minX(min.x), minY(min.y), maxX(max.x), maxY(max.y) {}

    /**
     * @brief Computes the minimal bounding box that encloses a set of points.
     * @param points The set of points to enclose.
     */
    void compute(const std::set<Point>& points);
};

/**
 * @brief Overloads the stream insertion operator for easy printing of BBox objects.
 * @param os The output stream.
 * @param bbox The BBox object to print.
 * @return A reference to the output stream.
 */
std::ostream& operator<< (std::ostream& os, const BBox& bbox);

#endif // BBOX_H
