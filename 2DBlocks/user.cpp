#include "input.h"
#include "World.h"

#include <iostream>
#include <string_view>
#include <utility>

namespace user
{
    // Print prompt and get Coord2D
    World::coord_type getCoord2DFromUser(std::string_view prompt)
    {
        std::cout << prompt;
        return { input::get<World::coord_type::axis_type>("X: "),
            input::get<World::coord_type::axis_type>("Y: ") };
    }

    // Print prompt until we get a valid Coord2D
    // Asks user to try again if invalid
    World::coord_type getValidCoord2DFromUser(std::string_view prompt,
        const World& world)
    {
        auto coord{ getCoord2DFromUser(prompt) };

        while (!coord.isInRangeOf(world))
        {
            std::cout << "Coordinate must be between " << world.begin()
                << " and " << world.end() - 1 << ", please try again.\n";
            coord = getCoord2DFromUser(prompt);
        }

        return coord;
    }

    // Get a top-right and bottom-left corner from user
    std::pair<const World::coord_type&, const World::coord_type&>
        getCoord2DCornersFromUser(
            std::string_view trPrompt, std::string_view blPrompt)
    { // I'm bad at function names
        auto tr{ getCoord2DFromUser(trPrompt) }; // Top-right
        auto bl{ getCoord2DFromUser(blPrompt) }; // Bottom-left

        while (!(bl <= tr)) // This isn't equivalent to `while (bl > tr)`,
        {                   // see Coord2D::operator<=
            std::cout << tr << " is not to the top right of " << bl << ", "
                "please try again.\n";
            tr = getCoord2DFromUser(trPrompt);
            bl = getCoord2DFromUser(blPrompt);
        }

        return { tr, bl };
    }
}