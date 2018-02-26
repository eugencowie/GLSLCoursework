#include "game.hpp"
#include "../engine/vertex.inl"
#include <glad/glad.h>
#include <vector>

Game::Game() :
	m_window("GFX Coursework", {1280, 720}), // Create window
	m_shader("res/shaders/textured"),         // Create shader
	m_mesh(m_shader, {
		{{-0.5f,  0.5f, 0}, {}, {1, 1, 1, 1}, {0, 0}}, // Left top
		{{-0.5f, -0.5f, 0}, {}, {1, 0, 0, 1}, {0, 1}}, // Left bottom
		{{ 0.5f,  0.5f, 0}, {}, {0, 1, 0, 1}, {1, 0}}, // Right top
		{{ 0.5f, -0.5f, 0}, {}, {0, 0, 1, 1}, {1, 1}}  // Right bottom
	}, {
		{0, 1, 2},
		{3, 2, 1}
	}, {
		make_shared<Texture>("res/textures/bricks.jpg")
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
