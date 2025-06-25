#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "core/Point.h"
#include "core/GameOfLife.h"

#include <set>

class GameBenchmark {

public:
    void setState(const std::set<Point>& cells) {
        game.aliveCells = cells;
    }

    const std::set<Point>& getState() const {
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
