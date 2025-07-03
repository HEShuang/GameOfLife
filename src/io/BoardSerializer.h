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
#include "core/BBox.h"
#include <string>
#include <unordered_set>

class BenchMark;

/**
 * @class BoardSerializer
 * @brief Provides static methods for loading and saving the board state.
 *
 * This class handles the translation between the internal set of live cell
 * coordinates and the text-file grid format ('*' for alive, '_' for dead).
 */
class BoardSerializer
{
    friend class BenchMark;
public:
    /**
     * @brief Loads a board state from a text file.
     * @param sInFile The path to the input file.
     * @param[out] aliveCells The set to be populated with the coordinates of live cells.
     * @return True if loading was successful, false otherwise.
     */
    static bool load(const std::string& sInFile, std::unordered_set<Point>& aliveCells);

    /**
     * @brief Saves the board state with a smart strategy based on pattern size.
     *
     * If the pattern's bounding box < MAX_DIMENSION, saves a single dense file ('*' for alive, '_' for dead).
     * If >= MAX_DIMENSION, saves 1) a sparse coordinate list, 2) a centered viewport, 3) ask user if to save a full dense file
     *
     * @param sOutFile The base path for the output file(s).
     * @param aliveCells The set of live cell coordinates to save.
     * @return True if saving was successful, false otherwise.
     */
    static bool save(const std::string& sOutFile, const std::unordered_set<Point>& aliveCells);

private:
    // --- Constants for the save strategy ---
    static const int MAX_DIMENSION = 1000; // Max dimension for a 'small' board
    static const int VIEWPORT_WIDTH = 200; // Width of the centered viewport
    static const int VIEWPORT_HEIGHT = 100; // Height of the centered viewport

    // Saves cells to a file in the dense (*_) format within a given bounding box.
    static bool saveDense(const std::string& sOutFile, const std::unordered_set<Point>& aliveCells, const BBox& bbox);

    // Saves cells to a file in a sparse (x,y coordinate list) format.
    static bool saveSparse(const std::string& sOutFile, const std::unordered_set<Point>& aliveCells);

    static Point findDensestRegionCenter(const std::unordered_set<Point>& aliveCells);
};

#endif // BOARDSERIALIZER_H
