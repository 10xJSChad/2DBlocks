#include "World.h"

#include <iostream>

// Prints m_grid with border
std::ostream& operator<< (std::ostream& out, const World& world)
{
    const auto width{ world.m_grid.size() };
    const auto height{ world.m_grid.at(0).size() };

    for (World::coord_type currentY{ world.getStartY() }; currentY < height;
        ++currentY)
    {
        if (currentY == world.getStartY())
        {
            out << world.horBorder().str() << '\n';
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
            out << world.horBorder().str() << '\n';
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
std::stringstream World::horBorder() const
{
    std::stringstream line{};
    for (coord_type currentX{ m_startX }; currentX < m_width + 2;
        ++currentX)
    {
        line << m_border.getType();
    }
    return line;
}