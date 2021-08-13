#ifndef COORD2D_H
#define COORD2D_H

#include <cstdint>
#include <iostream>

class World;

// Stores integral 2D coordinate
class Coord2D
{
public:
    using axis_type = std::int_fast64_t;
private:
    axis_type m_x{ 0 };
    axis_type m_y{ 0 };
public:
    Coord2D() = default;
    Coord2D(const axis_type x, const axis_type y);

    // ------------------------ Access functions ------------------------ //

    axis_type getX() const;
    axis_type getY() const;
    void setX(axis_type val);
    void setY(axis_type val);

    // ----------------------------- Utility ---------------------------- //

    bool isInRangeOf(const World& world) const;
};

// -------------------------------- Operators ------------------------------- //

// True if x > x AND y > y
bool operator> (const Coord2D& coord1, const Coord2D& coord2);
// True if x < x AND y < y
bool operator< (const Coord2D& coord1, const Coord2D& coord2);
// True if x >= x AND y >= y
bool operator>= (const Coord2D& coord1, const Coord2D& coord2);
// True if x <= x AND y <= y
bool operator<= (const Coord2D& coord1, const Coord2D& coord2);

Coord2D operator+ (const Coord2D& coord1, const Coord2D& coord2);
Coord2D operator+ (const Coord2D& coord1, int num);
Coord2D operator- (const Coord2D& coord1, const Coord2D& coord2);
Coord2D operator- (const Coord2D& coord1, int num);

// Print coordinates
std::ostream& operator<< (std::ostream& out, const Coord2D& coord);

#endif // !COORD2D_H