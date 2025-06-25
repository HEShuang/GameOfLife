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
#include <set>

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
    static bool load(const std::string& sInFile, std::set<Point>& aliveCells);

    /**
     * @brief Saves the board state with a smart strategy based on pattern size.
     *
     * If the pattern's bounding box is smaller than MAX_DIMENSION, saves a single dense file ('*' for alive, '_' for dead).
     * If larger, it saves two more files: a sparse coordinate list and a centered viewport,
     *
     * @param sOutFile The base path for the output file(s).
     * @param aliveCells The set of live cell coordinates to save.
     * @return True if saving was successful, false otherwise.
     */
    static bool save(const std::string& sOutFile, const std::set<Point>& aliveCells);

private:
    // --- Constants for the save strategy ---
    static const int MAX_DIMENSION = 1000; // Max width or height for a "small" board
    static const int VIEWPORT_WIDTH = 200; // Width of the centered viewport
    static const int VIEWPORT_HEIGHT = 100; // Height of the centered viewport

    // Saves cells to a file in the dense (*_) format within a given bounding box.
    static bool saveDense(const std::string& sOutFile, const std::set<Point>& aliveCells, const BBox& bbox);

    // Saves cells to a file in a sparse (x,y coordinate list) format.
    static bool saveSparse(const std::string& sOutFile, const std::set<Point>& aliveCells);

    static Point findDensestRegionCenter(const std::set<Point>& aliveCells);
};

#endif // BOARDSERIALIZER_H
