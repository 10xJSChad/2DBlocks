#ifndef WORLD_H
#define WORLD_H

#include "Coord2D.h"
#include "Tile.h"

#include <cassert>
#include <cstddef> // size_t
#include <iostream>
#include <sstream>
#include <vector>

class World
{
public:
    using coord_type = Coord2D;
private:
    using y_type = std::vector<Tile>;
    using x_type = std::vector<y_type>;
    x_type m_grid{};
    x_type m_backupGrid{};
    Coord2D m_start{ 0, 0 }; // Bottom-left
    Coord2D m_end{ 1, 1 };   // Top-right + { 1, 1 }

// The vector only takes positive numbers, so this offset is applied to indices
    Coord2D m_offset{ 0, 0 }; 

    const Tile m_empty{ ' ' };  // Air tile
    const Tile m_border{ '#' }; // Border
public:
    World() = default;
    World(const Coord2D& start, const Coord2D& end);

    // ------------------------ Access functions ------------------------ //

    const Tile& getTile(const Coord2D& coord) const;
    void place(const Tile& tile, const Coord2D& coord);
    void back();

    const Coord2D& begin() const { return m_start; } // Bottom-left
    const Coord2D& end()   const { return m_end; }   // Top-right + { 1, 1 }

    const Tile& getEmpty()  const { return m_empty; }  // Air tile
    const Tile& getBorder() const { return m_border; } // Border

    // ----------------------------- Utility ---------------------------- //

    void fill(const Tile& tile);
};

// -------------------------------- Operators ------------------------------- //

// Print world with border
std::ostream& operator<< (std::ostream& out, const World& world);

#endif