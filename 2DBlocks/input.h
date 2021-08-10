#ifndef INPUT_H
#define INPUT_H

class World;

#include <iostream>
#include <string>

namespace input
{
    // Clear the input buffer
    void ignoreLine();
}

// --------------------------------- Inline --------------------------------- //

namespace input
{
    // Print query and return user input
    template <typename Tret, typename Tquery>
    Tret get(Tquery query)
    {
        Tret ret{};
        while (true)
        {
            std::cout << query;
            std::cin >> ret;
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

        return ret;
    }
}

#endif // !INPUT_H