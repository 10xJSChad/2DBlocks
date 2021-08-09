#include "Tile.h"

#include <iostream>

std::ostream& operator<< (std::ostream& out, const Tile& tile)
{
    out << tile.m_type;

    return out;
}