#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "core/Point.h"
#include "core/GameOfLife.h"

#include <unordered_set>

class GameBenchmark {

public:
    void setState(const std::unordered_set<Point>& cells) {
        game.aliveCells = cells;
    }

    const std::unordered_set<Point>& getState() const {
        return game.aliveCells;
    }

    void nextGeneration() {
        game.nextGeneration();
    }

private:
    GameOfLife game;
};

class BenchMark {

public:
    static void populationCapacity();
    static void boardCapacity();

};

#endif
