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

// A helper template function to combine hashes, mimicking boost::hash_combine
template <class T>
inline void hash_combine(std::size_t& seed, const T& v) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std {
template <>
struct hash<Point> {
    std::size_t operator()(const Point& p) const noexcept {
        // Start with a seed of 0, then combine x and y into seed
        std::size_t seed = 0;
        hash_combine(seed, p.x);
        hash_combine(seed, p.y);
        return seed;
    }
};
}

#endif // POINT_H
