#include "gridhandling.h"
#include "interactive.h"
#include "world.h" // World structs, world::generate

#include <iostream> // std::cin and std::cout

int main()
{
	// Create world
	World overworld;

	// Get world dimensions
	overworld.xLength = interactive::getSize_tFromUser("How wide should the world be? ");
	overworld.yLength = interactive::getSize_tFromUser("How tall should the world be? ");

	// Create world grid
	// world::generate(overworld); // Doesn't work at the moment, for now we'll use the following instead:
	// ========================================================================
	std::cout << "Generating world...\n"
		<< "Tip: you can look at your world by pressing ENTER or L when the prompt shows up.\n"
		<< "Tip: the top-left tile is at X: 0 Y: 0\n"
		<< "Tip: you only need to type the letters in brackets to perform the specified action\n"
		<< "Tip: you can use lowercase and/or capital letters\n"
		<< "Tip: once I\'ve implemented multithreading, these tips will print as the world generates instead of printing instantly beforehand\n";

	overworld.grid = new Tile[overworld.xLength * overworld.yLength]{};
	std::cout << "Done!\n"
		<< "Tiles in world: " << overworld.xLength * overworld.yLength << " tiles\n"
		<< "Tiles on X axis: " << overworld.xLength << " tiles\n"
		<< "Tiles on Y axis: " << overworld.yLength << " tiles\n";
	// ========================================================================

	// Start interactive prompt
	do{}while 
		(!interactive::choose(interactive::prompt(), overworld));

	return 0;
}