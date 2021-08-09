#include "gridhandling.h"
#include "input.h"
#include "world.h" // Structs

#include <cassert> // assert

#include <iostream>
#include <limits> // numeric_limits

namespace input
{
	// Clear the input buffer
	void ignoreLine()
	{
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}

namespace interactive
{
	// Asks the user for the next action
	char prompt()
	{
		while (true)
		{
			auto choice{ input::get<char>("What do you want to do ([L]OOK/[P]lace/[D]estroy/[Q]uit)? ") };

			switch (choice)
			{
			case 'L':
			case 'l':
				return 'l'; // Returning l so we don't have to check 'L' or 0 later on
			case 'P':
			case 'p':
				return 'p';
			case 'D':
			case 'd':
				return 'd';
			case 'Q':
			case 'q':
				return 'q';
			default:
				std::cout << "Invalid, please try again:\n";
			};
		}
	}

	// Chooses an action based on the user's choice
	bool choose(char choice, World world)
	{
		switch (choice)
		{
		case 'l':
			std::cout << gridhandling::getGrid('#', world);
			return false;
		case 'p':
			interactive::promptPlace(world);
			return false;
		case 'd':
			interactive::promptDestroy(world);
			return false;
		case 'q':
			delete[] world.grid;
			return true;
		default:
			assert(!"Invalid choice passed from prompt()");
			break;
		}
		return true;
	}

	// Prompt the user to place a tile
	void promptPlace(World world)
	{
		int chosenX{ interactive::getXFromUser("Where do you want to place (X coordinate)? ", world) };
		int chosenY{ interactive::getYFromUser("Where do you want to place (Y coordinate)? ", world) };
		auto charsToPlace{ input::get<std::string>("What do you want to place (type any string)? ")};

		gridhandling::fillLines(chosenX, chosenY, charsToPlace, world);
		std::cout << '\'' << charsToPlace << "\' placed at X: " << chosenX << ", Y: " << chosenY << '\n';
	}

	void promptDestroy(World world)
	{
		int chosenX{ interactive::getXFromUser("Where do you want to start destroying (X coordinate)? ", world) };
		int chosenY{ interactive::getYFromUser("Where do you want to start destroying (Y coordinate)? ", world) };
		auto destroyCount{ input::get<int>("How many tiles do you want to destroy? ") };

		gridhandling::destroyLines(chosenX, chosenY, destroyCount, world);
	}

	int getXFromUser(std::string message, World world)
	{
		auto chosenX{ input::get<int>(message) };
		while (!isBetween(-1, world.xLength, chosenX))
		{
			chosenX = input::get<int>(message);
		}

		return chosenX;
	}
	
	int getYFromUser(std::string message, World world)
	{
		auto chosenY{ input::get<int>(message) };
		while (!isBetween(-1, world.yLength, chosenY))
		{
			chosenY = input::get<int>(message);
		}

		return chosenY;
	}

	// Checks whether toTest is between start and end
	bool isBetween(int start, int end, int toTest)
	{
		if (toTest > start && toTest < end)
		{
			return true;
		}
		else
		{
			std::cout << "Invalid, please enter a whole number between " << start << " and " << end << '\n';
			return false;
		}
	}

	void clearCinBuffer()
	{
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}