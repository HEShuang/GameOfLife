#include "GameOfLife.h"
#include "Exceptions.h"

void GameOfLife::nextGeneration() {

    if (aliveCells.size() > MAX_ALIVE_CELLS) {
        throw CapacityException("Exceeded maximum cell limit: " + std::to_string(MAX_ALIVE_CELLS));
    }

    //Count living neighbors of the given cell by iterating the 3x3 grid around
    auto countLiveNeighbors = [this](const Point& p) -> int{

        int nLive = 0;

        for (int dx = -1 ; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) { //Skip the cell itself
                    continue;
                }

                if (aliveCells.count({ p.x + dx, p.y + dy }))
                    nLive++;
            }
        }
        return nLive;
    };

    //Candidates to check living neighbors
    //A candicate for next generation is any currently live cell or any of its direct neighbors
    std::unordered_set<Point> candidates;
    for (const auto& cell : aliveCells) {
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                candidates.insert({cell.x + dx, cell.y + dy});
            }
        }
    }

    std::unordered_set<Point> nextAliveCells;
    for (const auto& cell: candidates) {
        int nLiveNB = countLiveNeighbors(cell);
        if (aliveCells.count(cell)) { //Rule 1: Any live cell with 2 or 3 live neighbors survives.
            if (nLiveNB == 2 || nLiveNB == 3) {
                nextAliveCells.insert(cell);
            }
        }
        else if (nLiveNB == 3) { // Rule 2: Any dead cell with 3 live neighbors becomes a live cell.
            nextAliveCells.insert(cell);
        }
        //Rule 3: All other live cells die in the next generation. Similarly, all other dead cells stay dead
        //No insert to nextAliveCells
    }

    aliveCells.swap(nextAliveCells);
}
