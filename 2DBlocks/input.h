#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <string>

namespace input
{
	// Clear the input buffer
    void ignoreLine();
}

namespace interactive
{
	char prompt();
	bool choose(char choice, World world);
	void promptPlace(World world);
	void promptDestroy(World world);

	int getXFromUser(std::string message, World world);
	int getYFromUser(std::string message, World world);

	bool isBetween(int start, int end, int toTest);
	void clearCinBuffer();
}

// --------------------------------- Inline --------------------------------- //

namespace input
{
    // Print query and return user input
    template <typename input, typename queryType>
    input get(queryType query)
    {
        input num{};
        while (true)
        {
            std::cout << query;
            std::cin >> num;
            ignoreLine();

            if (std::cin.fail())
            {
                std::cin.clear();
                ignoreLine();
                std::cout << "Invalid, please try again.\n";
            }
            else
            {
                break;
            }
        }

        return num;
    }
}

#endif // !INPUT_H