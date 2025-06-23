#include <gtest/gtest.h>
#include "core/GameOfLife.h"
#include "core/Point.h"

class GameTest: public ::testing::Test {
protected:
    GameOfLife game;

    void setState(const std::set<Point>& cells) {
        game.aliveCells = cells;
    }

    const std::set<Point>& getState() const {
        return game.aliveCells;
    }

    void nextGeneration() {
        game.nextGeneration();
    }
};

TEST_F(GameTest, BlockPatternIsStable) {
    // A 2x2 block is a "still life" and should not change.
    std::set<Point> block = {{0, 0}, {1, 0}, {0, 1}, {1, 1}};
    setState(block);

    nextGeneration();

    ASSERT_EQ(getState(), block);
}

TEST_F(GameTest, BlinkerPatternOscillates) {
    // A 1x3 horizontal line should become a 3x1 vertical line.
    std::set<Point> horizontalBlinker = {{0, 1}, {1, 1}, {2, 1}};
    setState(horizontalBlinker);

    // Generation 1 should turn to vertical
    nextGeneration();
    std::set<Point> verticalBlinker = {{1, 0}, {1, 1}, {1, 2}};
    ASSERT_EQ(getState(), verticalBlinker);

    // Generation 2 should return to original state
    nextGeneration();
    ASSERT_EQ(getState(), horizontalBlinker);
}

TEST_F(GameTest, GliderPatternMoves) {
    // A glider should move diagonally down and right.
    std::set<Point> glider_gen0 = {{1, 0}, {2, 1}, {0, 2}, {1, 2}, {2, 2}};
    setState(glider_gen0);

    // After 4 generations, it returns to the same shape, but shifted by (1, 1).
    std::set<Point> glider_gen4_expected = {{2, 1}, {3, 2}, {1, 3}, {2, 3}, {3, 3}};

    for (int i=0; i<4; ++i)
        nextGeneration();

    ASSERT_EQ(getState(), glider_gen4_expected);
}
