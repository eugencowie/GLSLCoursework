#include "game.hpp"
#include "../engine/vertex.inl"
#include <glad/glad.h>
#include <vector>

Game::Game() :
	m_window("GFX Coursework", {1280, 720}), // Create window
	m_shader("res/shaders/colored"),         // Create shader
	m_mesh(m_shader, {
		{{-0.5f,  0.5f, 0},{0, 0, 0, 1}}, // Top left
		{{-0.5f, -0.5f, 0},{1, 0, 0, 1}}, // Bottom left
		{{0.5f,  0.5f, 0},{0, 1, 0, 1}}, // Top right
		{{0.5f, -0.5f, 0},{0, 0, 1, 1}}  // Bottom right
	}, {
		{0, 1, 2},
		{3, 2, 1}
	})
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

	// Process input events
	m_input.processEvents(m_window.events());

	// Check input
	if (m_input.keyJustReleased(SDLK_ESCAPE))
		m_window.close();
}

void Game::render()
{
	// Clear the back buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw the quad
	m_mesh.draw();

	// Swap front and back buffers
	m_window.swapBuffers();
}
