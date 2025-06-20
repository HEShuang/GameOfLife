#include "BoardGenerator.h"
#include "BBox.h"

#include <iostream>
#include <cstring>

void printManual(const char* progName) {
    std::cerr << "\nUsage: " << progName << " --output <filepath> --size <row col> \n"
              << "Parameters:\n"
              << "  --output <filepath>   : Mandatory. Path to the generated board file.\n"
              << "  --size <number number>: Mandatory (default 20 20). Two positive integers for row and colomn.\n\n";
}

bool parseArguments(int argc, char* argv[], int& row, int& col, std::string& outFile) {

    if (argc <= 1) {
        std::cerr << "Error: --output file is mandatory.\n";
        return false;
    }

    for (int i = 1; i < argc; ++i) {

        auto arg = argv[i];

        if (strcmp(arg, "--output") == 0) {

            if (i + 1 < argc) {
                outFile = argv[++i];
            }
            else {
                std::cerr << "Error: --output file is mandatory.\n";
                return false;
            }
        }

        else if ( strcmp(arg, "--size") == 0 ) {

            if (i + 2 < argc) {
                try {
                    row = std::stoi(argv[++i]);
                    col = std::stoi(argv[++i]);
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Error: --size value must have two integer values.\n";
                    return false;
                } catch (const std::out_of_range& e) {
                    std::cerr << "Error: --size value is out of range.\n";
                    return false;
                }
            }
            else {
                std::cerr << "Error: --size requires two integer for row and colomn.\n";
                return false;
            }
        }

        else {
            std::cerr << "Error: Unknown argument '" << arg << "'\n";
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[] ) {

    int row = 20, col = 20;
    std::string outFile;

    if (!parseArguments(argc, argv, row, col, outFile) ) {
        printManual(argv[0]);
        return 1;
    }

    if (row == 0 || col == 0) {
        std::cerr << "Error: --size can't be 0.\n";
        printManual(argv[0]);
        return 1;
    }

    if (outFile.empty()) {
        std::cerr << "Error: --output file is empty.\n";
        printManual(argv[0]);
        return 1;
    }

    std::cout << "size:" << row << ", " << col << std::endl;
    std::cout << "output:" << outFile << std::endl;
    std::cout << "start generation" << std::endl;
    BBox bbox{{0,0}, {row-1, col-1}};
    if (!BoardGenerator::generateRandom(outFile, bbox) ) {
        std::cerr << "Error: Board generation failed.\n";
        return 1;
    }

    std::cout << "Board generation successful and saved to file " << outFile << std::endl;
    return 0;
}
