#include "BoardSerializer.h"
#include "core/BBox.h"

#include <fstream>
#include <iostream>
#include <map>
#include <iomanip>    // For std::setprecision
#include <algorithm>  // For std::transform
#include <cctype>     // For std::tolower

bool BoardSerializer::load(const std::string& sInFile, std::unordered_set<Point>& aliveCells) {

    std::ifstream inFile(sInFile);
    if (!inFile.is_open()) {
        std::cerr << "Error: can't open file for reading: " << sInFile << std::endl;
        return false;
    }

    aliveCells.clear();

    std::string line;
    size_t expectedLength = -1;

    //The top-left of the file is the origin (0,0)
    int y = 0;
    while (std::getline(inFile, line)) {

        //comment
        if (line.front() == '#')
            continue;

        //Validate each line has the same length
        if (expectedLength == -1) {
            expectedLength = line.length();
        }
        else if (expectedLength != line.length()) {
            std::cerr << "Error: invalid file format: all lines must have the same length" << std::endl;
            aliveCells.clear();
            return false;
        }

        int x = 0;
        for (const auto& c: line) {
            if (c != '*' && c != '_') {
                std::cerr << "Error: invalid character '" << c << "' in file" << std::endl;
                aliveCells.clear();
                return false;
            }

            else if (c == '*') {
                aliveCells.insert({x,y});
            }
            x++;
        }
        y++;
    }
    return true;
}

bool BoardSerializer::save(const std::string& sOutFile, const std::unordered_set<Point>& aliveCells) {

    if (aliveCells.empty()) {
        std::ofstream outFile(sOutFile);
        return outFile.good();
    }

    try {
        BBox bbox;
        bbox.compute(aliveCells);

        if (bbox.width < MAX_DIMENSION && bbox.height < MAX_DIMENSION) {
            std::cout << "Pattern is small. Saving to a single dense file: " << sOutFile << std::endl;
            return saveDense(sOutFile, aliveCells, bbox);
        }
        else {
            std::cout << "Pattern is large. Saving in different formats:" << std::endl;

            // Generate derived filenames by inserting suffixes before the extension.
            std::string baseName = sOutFile;
            std::string extension = "";
            size_t dotPos = sOutFile.find_last_of('.');
            if (dotPos != std::string::npos) {
                baseName = sOutFile.substr(0, dotPos);
                extension = sOutFile.substr(dotPos);
            }

            const std::string sparseFile = baseName + "_sparse" + extension;
            const std::string centerFile = baseName + "_center" + extension;

            // File 1 : Save the sparse file (coordinate dump)
            std::cout << "Saving sparse coordinate list to: " << sparseFile << std::endl;
            if (!saveSparse(sparseFile, aliveCells))
                return false;

            // File 2 : Save the centered viewport
            std::cout << "Saving centered viewport to: " << centerFile << std::endl;
            Point center = findDensestRegionCenter(aliveCells);
            BBox centerBox = {
                { center.x - VIEWPORT_WIDTH / 2, center.y - VIEWPORT_HEIGHT / 2 },
                { center.x + VIEWPORT_WIDTH / 2, center.y + VIEWPORT_HEIGHT / 2 }
            };
            if (!saveDense(centerFile, aliveCells, centerBox))
                return false;

            // Calculate estimated file size to inform the user
            long long estimated_size_bytes = static_cast<long long>(bbox.width) * bbox.height;
            double estimated_size_mb = static_cast<double>(estimated_size_bytes) / (1024.0 * 1024.0);

            // Warn the user and ask for confirmation
            std::cout << "\nWARNING: The full dense file will be very large." << std::endl;
            std::cout << "  - Dimensions: " << bbox.width << "x" << bbox.height << std::endl;
            std::cout << "  - Estimated size: " << std::fixed << std::setprecision(2) << estimated_size_mb << " MB" << std::endl;
            std::cout << "Do you want to proceed with saving this file? (y/n): ";

            std::string userInput;
            std::cin >> userInput;
            std::transform(userInput.begin(), userInput.end(), userInput.begin(), [](unsigned char c){
                return std::tolower(c);
            });

            if (userInput == "y" || userInput == "yes") {
                std::cout << "User confirmed. Saving full dense file..." << std::endl;
                if (!saveDense(sOutFile, aliveCells, bbox)) {
                    return false; // The full save failed
                }
            } else {
                std::cout << "Save of full dense file aborted by user." << std::endl;
            }

            return true;
        }
    } catch (const std::exception& e) {
        std::cerr << "An error occurred during save: " << e.what() << std::endl;
        return false;
    }

}

// --- Private  ---

bool BoardSerializer::saveDense(const std::string& sOutFile, const std::unordered_set<Point>& aliveCells, const BBox& bbox) {
    std::ofstream outFile(sOutFile);
    if (!outFile) {
        std::cerr << "Error: Could not open file for writing: " << sOutFile << std::endl;
        return false;
    }

    for (int y = bbox.minY; y <= bbox.maxY; ++y) {
        for (int x = bbox.minX; x <= bbox.maxX; ++x) {
            if (aliveCells.count({x, y})) {
                outFile << '*';
            }
            else {
                outFile << '_';
            }
        }
        outFile << '\n';
    }
    return outFile.good();
}

bool BoardSerializer::saveSparse(const std::string& sOutFile, const std::unordered_set<Point>& aliveCells) {
    std::ofstream outFile(sOutFile);
    if (!outFile) {
        std::cerr << "Error: Could not open file for writing: " << sOutFile << std::endl;
        return false;
    }
    // Simple header
    outFile << "# Sparse coordinate list (x,y) : " << aliveCells.size() << "\n";
    for (const auto& p : aliveCells) {
        outFile << p.x << "," << p.y << "\n";
    }
    return outFile.good();
}

//Grid binning to find the densest region center
Point BoardSerializer::findDensestRegionCenter(const std::unordered_set<Point>& aliveCells) {
    if (aliveCells.empty()) {
        return {0, 0};
    }

    // use half the viewport width as grid size.
    const int GRID_SIZE = VIEWPORT_WIDTH / 2;

    std::map<Point, int> gridCounts;

    // 1. Bin all live cells and count them
    for (const auto& cell : aliveCells) {
        int gridX = cell.x / GRID_SIZE;
        int gridY = cell.y / GRID_SIZE;
        gridCounts[{gridX, gridY}]++;
    }

    // 2. Find the grid bin with the most cells
    Point densestGridCoord = gridCounts.begin()->first;
    int maxCount = 0;

    for (const auto& pair : gridCounts) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            densestGridCoord = pair.first;
        }
    }

    // 3. Return the center of the densest grid bin
    int centerX = (densestGridCoord.x * GRID_SIZE) + (GRID_SIZE / 2);
    int centerY = (densestGridCoord.y * GRID_SIZE) + (GRID_SIZE / 2);

    return {centerX, centerY};
}
