/* =====================================================================================
 *
 * Filename:  BoardGenerator.h
 *
 * Description:  A utility class for creating initial board states.
 *
 * =====================================================================================
 */

#ifndef BOARDGENERATOR_H
#define BOARDGENERATOR_H

#include <string>

class BBox;

/**
 * @class BoardGenerator
 * @brief Provides static methods for generating game board.
 */
class BoardGenerator
{
public:
    /**
     * @brief Generates a board with a random pattern and saves it to a file.
     * @param sOutFile The path to the output file.
     * @param bbox A bounding box defining the dimensions of the random pattern.
     * @param aliveChance The probability (0.0 to 1.0) for any given cell to be alive, default is 0.5
     * @return True if the board was generated and saved successfully, false otherwise.
     */
    static bool generateRandom(const std::string& sOutFile, const BBox& bbox, float aliveChance = 0.5);
};

#endif // BOARDGENERATOR_H
