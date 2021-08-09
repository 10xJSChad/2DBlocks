#include "input.h"
#include "world.h"

#include <cassert>
#include <iostream>

// Returns true if in range
bool validateXCoord(const World& world, World::coord_type x)
{
    if (!world.testCoords(x))
    {
        std::cout << x << ": X coordinate must be between " << world.getStartX()
            << " and " << world.getWidth() - 1 << ", please try again.\n";
        return false;
    };
    return true;
}

// Returns true if in range
bool validateYCoord(const World& world, World::coord_type y)
{
    if (!world.testCoords(1, y))
    {
        std::cout << y << ": Y coordinate must be between " << world.getStartY()
            << " and " << world.getHeight() - 1 << ", please try again.\n";
        return false;
    };
    return true;
}

void promptDestroy(World& world)
{
    constexpr std::string_view xPrompt{ "What do you want to destroy (X "
        "coordinate)? "};
    auto chosenX{ input::get<World::coord_type>(xPrompt) };
    while (!validateXCoord(world, chosenX))
    {
        chosenX = input::get<World::coord_type>(xPrompt);
    }

    constexpr std::string_view yPrompt{
        "What do you want to destroy (Y coordinate)? "};
    auto chosenY{ input::get<World::coord_type>(yPrompt) };
    while (!validateYCoord(world, chosenY))
    {
        chosenY = input::get<World::coord_type>(yPrompt);
    }

    world.setTile(world.getEmpty(), chosenX, chosenY);
}

// Prompt the user to place a tile
void promptPlace(World& world)
{
    constexpr std::string_view xPrompt{
        "Where do you want to place (X coordinate)? "
    };
    auto chosenX{ input::get<World::coord_type>(xPrompt) };
    while (!validateXCoord(world, chosenX))
    {
        chosenX = input::get<World::coord_type>(xPrompt);
    }

    constexpr std::string_view yPrompt{
        "Where do you want to place (Y coordinate)? "
    };
    auto chosenY{ input::get<World::coord_type>(yPrompt) };
    while (!validateYCoord(world, chosenY))
    {
        chosenY = input::get<World::coord_type>(yPrompt);
    }

    constexpr std::string_view tilePrompt{
        "What tile do you want to place (single character)? "
    };
    auto chosenTileType{ input::get<Tile::type_type>(tilePrompt) };

    world.setTile(chosenTileType, chosenX, chosenY);
    std::cout << '\'' << chosenTileType << "\' placed at X: " << chosenX
        << ", Y: " << chosenY << '\n';
}

// Ask the user for the next action
// Returns false when done
bool prompt(World& world)
{
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

    constexpr std::string_view promptMsg{"What do you want to do (type help to "
        "list all commands)? "};
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
        switch (choice.at(0))
        {
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

int main()
{
    World overworld{
        input::get<World::coord_type>("How wide shall the world be? "),
        input::get<World::coord_type>("How tall shall the world be? ")
    };

    while (prompt(overworld));

    return 0;
}