/* =====================================================================================
 *
 * Filename:  Point.h
 *
 * Description:  Defines a simple struct to represent a 2D coordinate.
 *
 * =====================================================================================
 */
#ifndef POINT_H
#define POINT_H

/**
 * @struct Point
 * @brief Represents a 2D coordinate with integer x and y values.
 *
 * This struct is fundamental for representing cell locations on the infinite grid.
 * It includes comparison operators to allow it to be used as a key in std::set
 * and for equality checks in tests.
 */
struct Point {
    int x, y;
    bool operator < (const Point& other) const {
        return x != other.x ? x < other.x : y < other.y;
    }

    bool operator == (const Point& other) const {
        return x == other.x && y == other.y;
    }
};

#endif // POINT_H
