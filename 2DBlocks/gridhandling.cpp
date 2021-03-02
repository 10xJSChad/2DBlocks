#include "gridhandling.h" // gridhandling::getHorBorder
#include "world.h" // Structs

#include <cstddef> // std::size_t
#include <iostream> // std::cout
#include <string> // std::string

namespace gridhandling
{
    // Returns index of item in grid, parameters and result are zero-indexed
    int getTile(int X, int Y, World world)
    {
        return (Y * static_cast<int>(world.xLength) + X);
    }

    // Sets tile at X Y to type
    void setTile(int X, int Y, char type, World world)
    {
        world.grid[gridhandling::getTile(X, Y, world)].type = type;
    }

    // Fills the grid with tiles
    void fillGrid(char item, World world)
    {
        // Fill rows
        for (int currentY{ 0 }; currentY <= (world.yLength - 1); ++currentY)
        {
            // Fill columns
            for (int currentX{ 0 }; currentX <= (world.xLength - 1); ++currentX)
            {
                setTile(currentX, currentY, item, world);
            }
        }
    }

    // Returns `count` `character`s
    std::string getHorBorder(char character, World world)
    {
        std::string line{};
        for (int currentBorderColumn{ 0 }; currentBorderColumn < (world.xLength + 2); ++currentBorderColumn)
        {
            line += character;
        }
        line += '\n';

        return line;
    }

    // Returns the grid as a string
    std::string getGrid(char borderType, World world)
    {
        std::string gridString{};

        // For each row
        for (int currentY{ 0 }; currentY <= (world.yLength - 1); ++currentY)
        {
            // If first row, draw top border first
            if (currentY == 0)
            {
                gridString += gridhandling::getHorBorder(borderType, world);
            }

            // For each column in current row
            for (int currentX{ 0 }; currentX <= (world.xLength - 1); ++currentX)
            {
                // If first column, draw left border first
                if (currentX == 0)
                {
                    gridString += borderType;
                }

                // Draw column in current row
                gridString += world.grid[gridhandling::getTile(currentX, currentY, world)].type;

                // If last column, draw right border
                if (currentX == (world.xLength - 1))
                {
                    gridString += borderType;
                }
            }
            gridString += '\n';

            // If last row, draw right border
            if (currentY == (world.yLength - 1))
            {
                gridString += getHorBorder(borderType, world);
            }
        }

        return gridString;
    }

    // Fills from left to right and top to bottom with characters from `items`
    void fillLines(int X, int Y, std::string items, World world)
    {
        std::size_t length{ items.length() };
        int currentX{ X };
        int currentY{ Y };
        for (int currentItem{ 0 }; currentItem < length; ++currentItem)
        {
            world.grid[gridhandling::getTile(currentX, currentY, world)].type = items[currentItem];

            // If at end of row
            if (currentX == (world.xLength - 1))
            {
                // If at end of grid
                if (currentY == (world.yLength - 1))
                {
                    break; // We're done!
                }
                else // We're not done yet
                {
                    // Move to next row
                    ++currentY;
                    // Return to start of row
                    currentX = 0;
                }
            }
            else
            {
                ++currentX;
            }
        }
    }

    void destroyLines(int X, int Y, int count, World world)
    {
        int currentX{ X };
        int currentY{ Y };
        for (int currentItem{ 0 }; currentItem < count; ++currentItem)
        {
            world.grid[gridhandling::getTile(currentX, currentY, world)].type = ' ';

            // If at end of row
            if (currentX == (world.xLength - 1))
            {
                // If at end of grid
                if (currentY == (world.yLength - 1))
                {
                    break; // We're done!
                }
                else // We're not done yet
                {
                    // Move to next row
                    ++currentY;
                    // Return to start of row
                    currentX = 0;
                }
            }
            else
            {
                ++currentX;
            }
        }
    }

}