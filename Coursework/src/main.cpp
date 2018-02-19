#include <iostream>
#include <cassert>
#include <cstdlib>
#include <string>
#include <SDL.h>

using namespace std;

void panic(const string& message, const string& details = "")
{
	// Print error message to console
	cerr << message << endl << details << endl;

	// Attempt to trigger debugger
	assert(false);

	// Exit indicating failure
	exit(EXIT_FAILURE);
}

int main(int argc, char** argv)
{
	// Initialise SDL
	int sdl = SDL_Init(SDL_INIT_EVERYTHING);
	if (sdl != 0) panic("Failed to initialise SDL");

	// Set OpenGL attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	// Create window
	SDL_Window* window = SDL_CreateWindow("GFX Coursework", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_OPENGL);
	if (!window) panic("Failed to create SDL window");

	// Create OpenGL context
	SDL_GLContext context = SDL_GL_CreateContext(window);
	if (!context) panic("Failed to create OpenGL context");

	// Enable vertical synchronisation
	SDL_GL_SetSwapInterval(1);

	bool shouldClose = false;
	while (!shouldClose)
	{
		// Process window events
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				shouldClose = true;
				break;
			}
		}

		// Swap front and back buffers
		SDL_GL_SwapWindow(window);
	}

	// Destroy window and shutdown SDL
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}
