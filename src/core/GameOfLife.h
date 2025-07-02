/* =====================================================================================
 *
 * Filename:  GameOfLife.h
 *
 * Description:  The core class for the Game of Life simulation engine.
 *
 * This class manages the state of the simulation (the set of live cells)
 * and contains the logic for evolving the board to the next generation.
 *
 * =====================================================================================
 */
#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include "Point.h"
#include <unordered_set>

class GameController;
class GameTest;
class GameBenchmark;

/**
 * @class GameOfLife
 * @brief Manages the simulation state and implements the game's rules.
 *
 * The board is represented as an "infinite" grid by storing only the
 * coordinates of the currently alive cells in a std::set.
 */
class GameOfLife
{
    friend class GameController;
    friend class GameTest;
    friend class GameBenchmark;

public:
    /**
     * @brief Gets a constant reference to the set of currently alive cells.
     * @return A const reference to the set of Points representing live cells.
     */
    inline const std::unordered_set<Point>& getAliveCells() const noexcept { return aliveCells; }

private:
    /**
     * @brief Advances the simulation by one generation.
     *
     * This method applies the rules of the Game of Life to the current set
     * of aliveCells to compute the state for the next generation.
     */
    void nextGeneration();

    std::unordered_set<Point> aliveCells;

    static inline size_t MAX_ALIVE_CELLS = 2'000'000;
};

#endif // GAMEOFLIFE_H
