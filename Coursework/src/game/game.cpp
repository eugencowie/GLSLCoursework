#include "game.hpp"
#include <glad/glad.h>

Game::Game() :
	m_window("GFX Coursework", {1280, 720}) // Create window
{
	// Enable vertical synchronisation
	m_window.verticalSync(true);

	// Set up OpenGL
	glClearColor(0.4f, 0.6f, 0.9f, 1.0f);
}

void Game::run()
{
	while (!m_window.shouldClose())
	{
		// Update and render
		update();
		render();
	}
}

void Game::update()
{
	// Process window events
	m_window.processEvents();
}

void Game::render()
{
	// Clear the back buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Swap front and back buffers
	m_window.swapBuffers();
}
