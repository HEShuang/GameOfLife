#include <gtest/gtest.h>
#include "BoardSerializer.h"
#include "Point.h"
#include <set>
#include <fstream>
#include <string>

void createTestFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    file << content;
}

TEST(BoardSerializerTest, LoadValidFile) {
    const std::string filename = "test_load_valid.txt";
    createTestFile(filename, "_*\n*_\n");

    std::set<Point> aliveCells;
    ASSERT_TRUE(BoardSerializer::load(filename, aliveCells));

    std::set<Point> expected = {{1, 0}, {0, 1}};
    ASSERT_EQ(aliveCells, expected);

    std::remove(filename.c_str());
}

TEST(BoardSerializerTest, LoadInvalidCharacter) {
    const std::string filename = "test_load_invalid_char.txt";
    createTestFile(filename, "_X\n*_\n");

    std::set<Point> aliveCells;
    ASSERT_FALSE(BoardSerializer::load(filename, aliveCells));
    ASSERT_TRUE(aliveCells.empty());

    std::remove(filename.c_str());
}

TEST(BoardSerializerTest, SaveCorrectOutput) {
    const std::string filename = "test_save_output.txt";
    std::set<Point> cells = {{0, 0}, {2, 0}, {1, 1}}; // A small 'v' shape

    ASSERT_TRUE(BoardSerializer::save(filename, cells));

    std::ifstream file(filename);
    std::string line1, line2;
    std::getline(file, line1);
    std::getline(file, line2);

    ASSERT_EQ(line1, "*_*");
    ASSERT_EQ(line2, "_*_");

    std::remove(filename.c_str());
}
