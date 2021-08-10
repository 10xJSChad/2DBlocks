#include "input.h"
#include "world.h"

#include <iostream>

namespace input
{
    // Clear the input buffer
    void ignoreLine()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}