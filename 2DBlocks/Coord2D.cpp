#include "Coord2D.h"
#include "World.h"

#include <cassert>

Coord2D::Coord2D(const axis_type x, const axis_type y)
    : m_x{ x }, m_y{ y } {}

Coord2D::axis_type Coord2D::getX() const
{
    return m_x;
}

Coord2D::axis_type Coord2D::getY() const
{
    return m_y;
}

void Coord2D::setX(Coord2D::axis_type val)
{
    m_x = val;
}

void Coord2D::setY(Coord2D::axis_type val)
{
    m_y = val;
}

bool Coord2D::isInRangeOf(const World& world) const
{
    return *this >= world.begin() && *this < world.end();
}

// True if x > x AND y > y
bool operator> (const Coord2D& coord1, const Coord2D& coord2)
{
    return (coord1.getX() > coord2.getX()) && (coord1.getY() > coord2.getY());
}

// True if x < x AND y < y
bool operator< (const Coord2D& coord1, const Coord2D& coord2)
{
    return (coord1.getX() < coord2.getX()) && (coord1.getY() < coord2.getY());
}

// True if x >= x AND y >= y
bool operator>= (const Coord2D& coord1, const Coord2D& coord2)
{
    return (coord1.getX() >= coord2.getX()) && (coord1.getY() >= coord2.getY());
}

// True if x <= x AND y <= y
bool operator<= (const Coord2D& coord1, const Coord2D& coord2)
{
    return (coord1.getX() <= coord2.getX()) && (coord1.getY() <= coord2.getY());
}

Coord2D operator+ (const Coord2D& coord, int num)
{
    return { coord.getX() + num, coord.getY() + num };
}

Coord2D operator+ (const Coord2D& coord1, const Coord2D& coord2)
{
    return { coord1.getX() + coord2.getX(), coord1.getY() + coord2.getY() };
}

Coord2D operator- (const Coord2D& coord, int num)
{
    return { coord.getX() - num, coord.getY() - num };
}

Coord2D operator- (const Coord2D& coord1, const Coord2D& coord2)
{
    return { coord1.getX() - coord2.getX(), coord1.getY() - coord2.getY() };
}

// Print coordinates
std::ostream& operator<< (std::ostream& out, const Coord2D& coord)
{ // TODO: color
    out << "X: " << coord.getX() << ", Y: " << coord.getY();

    return out;
}