#include "world.h" // World structs

#include <iostream> // std::cout

namespace world
{
	// Generates world and prints useful information
	void generate(World world)
	{
		std::cout << "Generating world...\n"
			<< "Tip: you can look at your world by pressing ENTER or L when the prompt shows up.\n"
			<< "Tip: the top-left tile is at X: 0 Y: 0\n"
			<< "Tip: you only need to type the letters in brackets to perform the specified action\n"
			<< "Tip: you can use lowercase and/or capital letters\n"
			<< "Tip: once I\'ve implemented multithreading, these tips will print as the world generates instead of printing instantly beforehand\n";

		std::size_t xLength{ world.xLength };
		std::size_t yLength{ world.yLength };
		world.grid = new Tile[xLength * yLength]{};
		std::cout << "Done!\n"
			<< "Tiles in world: " << xLength * yLength << " tiles\n"
			<< "Tiles on X axis: " << xLength << " tiles\n"
			<< "Tiles on Y axis: " << yLength << " tiles\n";
	}
}