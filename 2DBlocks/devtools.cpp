#include <iostream> // std::cout
#include <limits> // std::numeric_limits

namespace devtools
{
	void printASCIIList()
	{
		for (int i{ 0 }; i < std::numeric_limits<char>::max(); ++i)
		{
			std::cout << static_cast<char>(i) << '\n';
		}
	}
}