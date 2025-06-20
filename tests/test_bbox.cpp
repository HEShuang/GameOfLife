#include <gtest/gtest.h>
#include <set>
#include "BBox.h"
#include "Point.h"

TEST(BBoxTest, ComputesCorrectBounds) {
    std::set<Point> cells = {{1, 2}, {-3, 5}, {10, -1}};
    BBox bbox;
    bbox.compute(cells);

    ASSERT_EQ(bbox.minX, -3);
    ASSERT_EQ(bbox.maxX, 10);
    ASSERT_EQ(bbox.minY, -1);
    ASSERT_EQ(bbox.maxY, 5);
}

TEST(BBoxTest, SinglePoint) {
    std::set<Point> cells = {{5, 5}};
    BBox bbox;
    bbox.compute(cells);

    ASSERT_EQ(bbox.minX, 5);
    ASSERT_EQ(bbox.maxX, 5);
    ASSERT_EQ(bbox.minY, 5);
    ASSERT_EQ(bbox.maxY, 5);
}

TEST(BBoxTest, EmptySet) {
    std::set<Point> cells;
    BBox bbox;
    // The compute function should handle this gracefully (e.g., by doing nothing or resetting to zero).
    // Let's assume it resets to default values.
    bbox.compute(cells);

    ASSERT_EQ(bbox.minX, 0); // Or whatever you define as the default
    ASSERT_EQ(bbox.minY, 0);
}
