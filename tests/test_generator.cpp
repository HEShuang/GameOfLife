#include <gtest/gtest.h>
#include "io/BoardGenerator.h"
#include "io/BoardSerializer.h"
#include "core/BBox.h"
#include "core/Point.h"

#include <fstream>
#include <string>
#include <set>
#include <filesystem>

std::string readFileContent(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return "";
    }
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

TEST(BoardGeneratorTest, GeneratesAllDeadBoard) {
    // Test with aliveChance = 0.0. The board file should be empty.
    std::string file = (std::filesystem::temp_directory_path() / "test_all_dead.txt").string();
    BBox bbox{{0, 0}, {4, 3}}; // A 5x4 board

    ASSERT_TRUE(BoardGenerator::generateRandom(file, bbox, 0.0f));

    std::string content = readFileContent(file);
    std::string expected_content = "";
    ASSERT_EQ(content, expected_content);

    std::filesystem::remove(file);
}

TEST(BoardGeneratorTest, GeneratesAllLiveBoard) {
    // Test with aliveChance = 1.0. The board should be entirely live cells ('*').
    std::string file = (std::filesystem::temp_directory_path() / "test_all_live.txt").string();
    BBox bbox{{0, 0}, {3, 2}}; // A 4x3 board

    ASSERT_TRUE(BoardGenerator::generateRandom(file, bbox, 1.0f));

    std::string content = readFileContent(file);
    std::string expected_content = "****\n****\n****\n";
    ASSERT_EQ(content, expected_content);

    std::filesystem::remove(file);
}

TEST(BoardGeneratorTest, GeneratedFileIsValidAndHasCorrectDimensions) {
    // Test if a randomly generated file can be successfully loaded back,
    // Also check its dimensions.
    std::string file = (std::filesystem::temp_directory_path() / "test_validity.txt").string();
    BBox bbox{{0, 0}, {19, 9}}; // A 20x10 board

    ASSERT_TRUE(BoardGenerator::generateRandom(file, bbox, 0.5f));

    // Check if the file can be loaded by the serializer without errors
    std::unordered_set<Point> loaded_cells;
    ASSERT_TRUE(BoardSerializer::load(file, loaded_cells));

    // Check the dimensions by reading the file line by line
    {
        std::ifstream inFile(file);
        std::string line;
        int line_count = 0;
        while (std::getline(inFile, line)) {
            // Check that all lines have the correct width (20 characters)
            ASSERT_EQ(line.length(), 20);
            line_count++;
        }
        // Check that the file has the correct height (10 lines)
        ASSERT_EQ(line_count, 10);
    }

    std::filesystem::remove(file);
}
