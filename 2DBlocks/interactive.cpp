#include "gridhandling.h"
#include "interactive.h"
#include "world.h" // Structs

#include <cassert> // assert
#include <iostream> // std::cin and std::cout


namespace interactive
{
	// Asks the user for the next action
	char prompt()
	{
		while (true)
		{
			char choice{ interactive::getCharFromUser("What do you want to do [[L]OOK/[P]lace/[D]estroy/[Q]uit]? ") };

			switch (choice)
			{
			case 'L':
			case 'l':
			case 0: // If no input is given
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
		int chosenX{ interactive::getIntFromUser("Where do you want to place (X coordinate)? ") };
		int chosenY{ interactive::getIntFromUser("Where do you want to place (Y coordinate)? ") };
		std::string charsToPlace{ interactive::getStringFromUser("What do you want to place (type any string) ? ")};

		gridhandling::fillLines(chosenX, chosenY, charsToPlace, world);
		std::cout << '\'' << charsToPlace << "\' placed at X: " << chosenX << ", Y: " << chosenY << '\n';
	}

	void promptDestroy(World world)
	{
		int chosenX{ getIntFromUser("Where do you want to start destroying (X coordinate)? ") };
		int chosenY{ getIntFromUser("Where do you want to start destroying (Y coordinate)? ") };
		int destroyCount{ interactive::getIntFromUser("How many tiles do you want to destroy(default: 1) ? ") };

		gridhandling::destroyLines(chosenX, chosenY, destroyCount, world);
	}

	// Gets integer entered by the user
	int getIntFromUser(std::string message)
	{
		int result{};
		do
		{
			std::cout << message;
			std::cin >> result;
			interactive::clearCinBuffer();
		} while (interactive::isBadInput());

		return result;
	}

	// Gets the first character entered by the user
	char getCharFromUser(std::string message)
	{
		std::string reply{};

		do
		{
			std::cout << message;
			std::getline(std::cin, reply);
		} while (interactive::isBadInput());

		return reply[0];
	}

	std::string getStringFromUser(std::string message)
	{
		std::string reply{};

		do
		{
			std::cout << message;
			std::getline(std::cin, reply);
		} while (interactive::isBadInput());

		return reply;
	}

	// Gets std::size_t entered by the user
	size_t getSize_tFromUser(std::string message)
	{
		size_t result{};
		do
		{
			std::cout << message;
			std::cin >> result;
			interactive::clearCinBuffer();
		} while (interactive::isBadInput());

		return result;
	}

	// Checks for cin fail state
	bool isBadInput()
	{
		if (std::cin.fail())
		{
			std::cout << "Invalid, please try again.\n";
			std::cin.clear();
			interactive::clearCinBuffer();
			return true;
		}
		else
		{
			return false;
		}
	}

	void clearCinBuffer()
	{
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}