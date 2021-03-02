#ifndef WORLD_H
#define WORLD_H

#include <cstddef> // std::size_t

struct Tile
{
    char type{ ' ' };
};

struct World
{
    // Flattened two-dimensional array
    Tile* grid{};
    std::size_t xLength{};
    std::size_t yLength{};
};

namespace world
{
    void generate(World world);
}

#endif