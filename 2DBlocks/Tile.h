#ifndef TILE_H
#define TILE_H

#include <iostream>

class Tile
{
public:
    using type_type = char;
private:
    type_type m_type{ ' ' };
public:
    Tile() = default;
    Tile(type_type type) : m_type{ type } {}

    inline type_type getType() const { return m_type; }

    friend std::ostream& operator<< (std::ostream& out, const Tile& tile);
};

#endif // !TILE_H