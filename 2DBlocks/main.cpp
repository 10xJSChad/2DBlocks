#include "input.h"
#include "user.h"
#include "World.h"

#include <cassert>
#include <iostream>
#include <string_view>

// Ask the user for the next action
// Returns false when done
bool prompt(World& world);

// Prompt the user to place a tile
void promptPlace(World& world);

// Prompt the user to destroy a tile
void promptDestroy(World& world);

int main()
{
    const auto corners{ user::getCoord2DCornersFromUser(
        "Where should the top-right corner be?\n",
        "And the bottom-left corner?\n") 
    };

    World overworld{ corners.second, corners.first + 1 };
    while (prompt(overworld));

    return 0;
}

// Ask the user for the next action
// Returns false when done
bool prompt(World& world)
{ // TODO: Horizontal > navigation > bar
    auto printHelp{
        []()
        {
            std::cout << "All commands:\n"
                "\n"
                "  Game\n"
                "    help      show this help screen\n"
                "    quit      end the game\n"
                "\n"
                "  World\n"
                "    print     show the world grid\n"
                "    place     place a single block\n"
                "    destroy   break a single block\n";
        }
    };

    constexpr std::string_view promptMsg{ "What do you want to do (type help to "
        "list all commands)? " };
    auto choice{ input::get<std::string>(promptMsg) };

    auto printInvalid{
        [&]()
        {
            std::cout << choice << ": Unknown command, please try again."
                << '\n';
        }
    };
    while (true)
    {
        // TODO: implement a dynamic way of doing this, e.g. an array of tuples
        // that stores names, descriptions and function pointers. Should then
        // also update printHelp().
        switch (choice.at(0))
        {
        case 'B':
        case 'b':
            world.back();
            break;
        case 'H':
        case 'h':
            printHelp();
            break;
        case 'P':
        case 'p':
            if (choice.size() > 1)
            {
                switch (choice.at(1))
                {
                case 'R':
                case 'r':
                    std::cout << world;
                    return true;
                case 'L':
                case 'l':
                    promptPlace(world);
                    return true;
                default:
                    printInvalid();
                }
            }
            else
            {
                printInvalid();
            }
            break; // TODO: b to go back
        case 'D':
        case 'd':
            promptDestroy(world);
            return true;
        case 'Q':
        case 'q':
            return false;
        default:
            printInvalid();
        };
        choice = input::get<std::string>(promptMsg);
    }
}

// Prompt the user to place a tile
void promptPlace(World& world)
{
    constexpr std::string_view prompt{ "Where do you want to place?\n" };
    auto coord{ user::getValidCoord2DFromUser(prompt, world) };

    constexpr std::string_view tilePrompt{
        "What do you want to place (single character)? "
    };
    auto chosenTileType{ input::get<Tile::type_type>(tilePrompt) };

    world.place(chosenTileType, coord);
    std::cout << '\'' << chosenTileType << "\' placed at " << coord << '\n';
}

// Prompt the user to destroy a tile
void promptDestroy(World& world)
{
    constexpr std::string_view prompt{ "What do you want to destroy?\n" };
    auto coord{ user::getValidCoord2DFromUser(prompt, world) };

    world.place(world.getEmpty(), coord);
}