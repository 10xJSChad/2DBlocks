#ifndef USER_H
#define USER_H

#include "World.h"

#include <string_view>
#include <utility>

namespace user
{
    // Print prompt and get Coord2D
    World::coord_type getCoord2DFromUser(std::string_view prompt);

    // Print prompt until we get a valid Coord2D
    // Asks user to try again if invalid
    World::coord_type getValidCoord2DFromUser(std::string_view prompt,
        const World&);

    // Get a top-right and bottom-left corner from user
    std::pair<const World::coord_type&, const World::coord_type&>
        getCoord2DCornersFromUser(
            std::string_view trPrompt, std::string_view blPrompt);
}

#endif // !USER_H