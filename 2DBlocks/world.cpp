#include "World.h"

#include <algorithm>
#include <string>
#include <iostream>

// Prints m_grid with border
std::ostream& operator<< (std::ostream& out, const World& world)
{
    const auto width{ world.m_grid.size() };
    const auto height{ world.m_grid.at(0).size() };
    const auto horizontalBorder{ world.horBorder() };

    for (World::coord_type currentY{ world.getStartY() }; currentY < height;
        ++currentY)
    {
        if (currentY == world.getStartY())
        {
            out << horizontalBorder << '\n';
        }

        for (World::coord_type currentX{ 0 }; currentX < width; ++currentX)
        {
            if (currentX == world.getStartX())
            {
                out << world.m_border;
            }

            out << world.m_grid.at(currentX).at(currentY);

            if (currentX == width - 1)
            {
                out << world.m_border;
            }
        }
        out << '\n';

        if (currentY == height - 1)
        {
            out << horizontalBorder << '\n';
        }
    }

    return out;
}

// Fills the world with Tiles
void World::fill(const Tile& tile)
{
    for (coord_type currentY{ 0 }; currentY < m_height; ++currentY)
    {
        for (coord_type currentX{ 0 }; currentX < m_width; ++currentX)
        {
            setTile(tile, currentX, currentY);
        }
    }
}

// Get horizontal border
std::string World::horBorder() const
{
    std::string line{};
    line.resize(m_width + 2);
    std::fill(line.begin(), line.end(), m_border.getType());

    return line;
}