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

#include <functional>
/**
 * @struct Point
 * @brief Represents a 2D coordinate with integer x and y values.
 *
 * This struct is fundamental for representing cell locations on the infinite grid.
 * It includes comparison operators to allow it to be used as a key in std::set, std::unordered_set
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

// Hash function specialization in the std namespace
namespace std {
template <>
struct hash<Point> {
    std::size_t operator()(const Point& p) const noexcept {
        auto h1 = std::hash<int>()(p.x);
        auto h2 = std::hash<int>()(p.y);
        return h1 ^ (h2 << 1); // Combine hashes
    }
};
}

#endif // POINT_H
