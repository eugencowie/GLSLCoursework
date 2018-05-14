#ifdef _DEBUG
#error Please run in Release mode for better framerate
#endif

#include "game/game.hpp"
#include <cstdlib>

int main(int argc, char** argv)
{
	// Create a new instance of the game
	Game game;

	// Run the game
	game.run();

	// Indicate successful completion
	return EXIT_SUCCESS;
}
