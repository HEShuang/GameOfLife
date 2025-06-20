#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include "Point.h"
#include <set>

class GameController;
class GameTest;

class GameOfLife
{
    friend class GameController;
    friend class GameTest;

    void nextGeneration();

    std::set<Point> aliveCells;
};

#endif // GAMEOFLIFE_H
