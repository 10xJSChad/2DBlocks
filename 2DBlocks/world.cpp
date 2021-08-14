#include "Coord2D.h"
#include "World.h"

#include <algorithm>
#include <string>
#include <iostream>

// Constructor which takes 2 corners
World::World(const Coord2D& start, const Coord2D& end)
    : m_start{ start }, m_end{ end },
    m_offset{ -(start.getX()), -(start.getY()) }
{
    assert(start < end && "bottom-left corner should go first");

    const auto size(m_end - m_start);
    m_grid.resize(size.getX());

    for (x_type::size_type i{ 0 }; i != (m_end + m_offset).getX(); ++i)
    {
        m_grid.at(i).resize(size.getY());
    }
    m_backupGrid = m_grid;
};

// Return a line of chr (no trailing new-line)
std::string charLine(char chr, int length)
{
    std::string line{};
    line.resize(length);
    std::ranges::fill(line, chr);

    return line;
}

// Print world with border
std::ostream& operator<< (std::ostream& out, const World& world)
{ // TODO: color, coordinates
    const auto startX{ world.begin().getX() };
    const auto startY{ world.begin().getY() };
    const auto endX{ world.end().getX() };
    const auto endY{ world.end().getY() };

    const auto borderChar{ world.getBorder().getType() };

    const auto horizontalBorder{
        charLine(borderChar, endX - startX + 2) }; // 2 corners

    for (World::coord_type::axis_type currentY{ startY }; currentY < endY;
        ++currentY)
    {
        if (currentY == startY)
        {
            out << horizontalBorder << '\n';
        }

        for (World::coord_type::axis_type currentX{ startX }; currentX < endX;
            ++currentX)
        {
            if (currentX == startX)
            {
                out << borderChar;
            }

            out << world.getTile(Coord2D{ currentX, currentY });

            if (currentX == endX - 1)
            {
                out << borderChar;
            }
        }
        out << '\n';

        if (currentY == endY - 1)
        {
            out << horizontalBorder << '\n';
        }
    }

    return out;
}

// Fill the world with tiles
void World::fill(const Tile& tile)
{
    for (coord_type::axis_type y{ m_start.getY() }; y < m_end.getY(); ++y)
    {
        for (coord_type::axis_type x{ m_start.getX() }; x < m_end.getX(); ++x)
        {
            place(tile, Coord2D{ x, y });
        }
    }
}

// Return the Tile at coord
const Tile& World::getTile(const Coord2D& coord) const
{
    assert(coord.isInRangeOf(*this));

    const auto index{ coord + m_offset };
    return m_grid.at(index.getX()).at(index.getY());
}

// Set the Tile at coord
void World::place(const Tile& tile, const Coord2D& coord)
{
    assert(coord.isInRangeOf(*this));

    const auto index{ coord + m_offset };
    m_backupGrid = m_grid;
    m_grid.at(index.getX()).at(index.getY()) = tile;
}

void World::back() {
    x_type temp = m_grid;
    m_grid = m_backupGrid;
    m_backupGrid = temp;
}