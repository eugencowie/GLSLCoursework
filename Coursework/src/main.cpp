#include "engine/window.hpp"
#include <glad/glad.h>

int main(int argc, char** argv)
{
	// Create window
	Window window("GFX Coursework", 1280, 720);

	// Enable vertical synchronisation
	window.verticalSync(true);

	// Set up OpenGL
	glClearColor(0.4f, 0.6f, 0.9f, 1.0f);

	while (!window.shouldClose())
	{
		// Process window events
		window.processEvents();

		// Clear the back buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Swap front and back buffers
		window.swapBuffers();
	}

	return EXIT_SUCCESS;
}
