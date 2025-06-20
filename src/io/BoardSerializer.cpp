#include "BoardSerializer.h"
#include "BBox.h"

#include <fstream>
#include <iostream>

bool BoardSerializer::load(const std::string& sInFile, std::set<Point>& aliveCells) {

    std::ifstream inFile(sInFile);
    if (!inFile.is_open()) {
        std::cerr << "Error: can't open file for reading: " << sInFile << std::endl;
        return false;
    }

    aliveCells.clear();

    std::string line;
    auto expectedLength = -1ll;

    //The top-left of the file is the origin (0,0)
    int y = 0;
    while (std::getline(inFile, line)) {

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

bool BoardSerializer::save(const std::string& sOutFile, const std::set<Point>& aliveCells) noexcept {

    std::ofstream outFile(sOutFile);

    if (!outFile.is_open()) {
        std::cerr << "Error: could not open file for writing: " << sOutFile << std::endl;
        return false;
    }

    //Empty board, empty file
    if (aliveCells.empty())
        return true;

    //Find the bounding box of the living cells
    BBox bbox;
    bbox.compute(aliveCells);

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
    return true;
}

void BoardSerializer::print(const std::set<Point>& aliveCells) noexcept {
    //Find the bounding box of the living cells
    BBox bbox;
    bbox.compute(aliveCells);
    std::cout<< bbox;

    for (int y = bbox.minY; y <= bbox.maxY; ++y) {
        for (int x = bbox.minX; x <= bbox.maxX; ++x) {
            if (aliveCells.count({x, y})) {
                std::cout << '*';
            }
            else {
                std::cout << '_';
            }
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
}
