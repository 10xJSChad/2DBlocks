#ifndef WORLD_H
#define WORLD_H

#include "Tile.h"

#include <cassert>
#include <cstddef> // size_t
#include <iostream>
#include <sstream>
#include <vector>

class World
{
public:
    using coord_type = std::size_t;
private:
    std::vector<std::vector<Tile>> m_grid; // outer vector is x, inner y
    const Tile m_border{ '#' };
    coord_type m_width;
    coord_type m_height;

    // Air block
    const Tile m_empty{ ' ' };

    // Minimum coordinates
    constexpr static coord_type m_startX{ 0 };
    constexpr static coord_type m_startY{ 0 };

    // Get horizontal border
    std::stringstream horBorder() const;
public:
    World(coord_type width = 1, coord_type height = 1)
    {
        setWidth(width);
        setHeight(height);
    };

    inline const Tile& getTile(const coord_type x, const coord_type y) const
    {
        checkCoords(x, y);
        return m_grid.at(x).at(y);
    }
    inline void setTile(const Tile& tile, const coord_type x, 
        const coord_type y)
    {
        checkCoords(x, y);
        m_grid.at(x).at(y) = tile;
    }

    inline coord_type getWidth() const { return m_width; }
    inline void setWidth(const coord_type width)
    {
        assert(width > 0);
        m_width = width;
        m_grid.resize(width);
    }

    inline coord_type getHeight() const { return m_height; }
    inline void setHeight(const coord_type height)
    {
        assert(height > 0);
        m_height = height;
        for (auto& col : m_grid)
        {
            col.resize(height);
        }
    }

    inline coord_type getStartX() const { return m_startX; }
    inline coord_type getStartY() const { return m_startY; }

    inline const Tile& getEmpty() { return m_empty; }

    friend std::ostream& operator<< (std::ostream& out, const World& world);

    // Asserts if coords are not in range
    inline void checkCoords(const coord_type x, const coord_type y = m_startY) 
        const
    {
        assert(x >= m_startX && x < getWidth());

        // x is checked first, otherwise this wouldn't be safe
        assert(y >= m_startY && y < getHeight());
    }

    // Returns false if coords are not in range
    inline bool testCoords(const coord_type x, const coord_type y = m_startY) 
        const
    {
        return (x >= m_startX && x < getWidth()) 
            && (y >= m_startY && y < getHeight());
    }

    void fill(const Tile& tile);
};

#endif