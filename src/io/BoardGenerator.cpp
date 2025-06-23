#include "BoardGenerator.h"

#include "BoardSerializer.h"
#include "core/BBox.h"
#include "core/Point.h"

#include <random>
#include <set>

bool BoardGenerator::generateRandom(const std::string& sOutFile, const BBox& bbox, float aliveChance) {


    std::mt19937 gen(std::random_device{}());
    std::bernoulli_distribution distribution(aliveChance);

    std::set<Point> aliveCells;

    for (int y = bbox.minY; y <= bbox.maxY; ++y) {
        for (int x = bbox.minX; x <= bbox.maxX; ++x) {
            if (distribution(gen)) {
                aliveCells.insert({x, y});
            }
        }
    }

    return BoardSerializer::save(sOutFile, aliveCells);
}
