#ifndef BOARDGENERATOR_H
#define BOARDGENERATOR_H

#include <string>

class BBox;
class BoardGenerator
{
public:
    static bool generateRandom(const std::string& sOutFile, const BBox& bbox, float aliveChance = 0.5);
};

#endif // BOARDGENERATOR_H
