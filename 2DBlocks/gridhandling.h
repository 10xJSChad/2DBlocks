#ifndef GRIDHANDLING_H
#define GRIDHANDLING_H

#include "world.h" // Structs

#include <cstddef> // std::size_t
#include <string> // std::string

namespace gridhandling
{
    int getTile(int X, int Y, World world);
    void setTile(int X, int Y, char type, World world);
    void fillGrid(char item, World world);

    std::string getHorBorder(char character, World world);

    std::string getGrid(char borderType, World world);

    void fillLines(int X, int Y, std::string items, World world);
    void destroyLines(int X, int Y, int count, World world);
}

#endif