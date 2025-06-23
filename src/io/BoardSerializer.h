/* =====================================================================================
 *
 * Filename:  BoardSerializer.h
 *
 * Description:  A utility class for saving and loading the board state to and from text files.
 *
 * =====================================================================================
 */

#ifndef BOARDSERIALIZER_H
#define BOARDSERIALIZER_H

#include "core/Point.h"
#include <string>
#include <set>

/**
 * @class BoardSerializer
 * @brief Provides static methods for loading and saving the board state.
 *
 * This class handles the translation between the internal set of live cell
 * coordinates and the text-file grid format ('*' for alive, '_' for dead).
 */
class BoardSerializer
{
public:
    /**
     * @brief Loads a board state from a text file.
     * @param sInFile The path to the input file.
     * @param[out] aliveCells The set to be populated with the coordinates of live cells.
     * @return True if loading was successful, false otherwise.
     */
    static bool load(const std::string& sInFile, std::set<Point>& aliveCells) noexcept;

    /**
     * @brief Saves the current board state to a text file.
     *
     * This method calculates the minimal bounding box of live cells and writes
     * only that portion to the file.
     * @param sOutFile The path to the output file.
     * @param aliveCells The set of live cell coordinates to save.
     * @return True if saving was successful, false otherwise.
     */
    static bool save(const std::string& sOutFile, const std::set<Point>& aliveCells) noexcept;
};

#endif // BOARDSERIALIZER_H
