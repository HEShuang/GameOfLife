#ifndef BOARDSERIALIZER_H
#define BOARDSERIALIZER_H

#include "Point.h"
#include <string>
#include <set>

class BoardSerializer
{
public:
    static bool load(const std::string& sInFile, std::set<Point>& aliveCells);
    static bool save(const std::string& sOutFile, const std::set<Point>& aliveCells) noexcept;
    static void print(const std::set<Point>& aliveCells) noexcept;
};

#endif // BOARDSERIALIZER_H
