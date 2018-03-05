#include "game.hpp"

#include <glad/glad.h>

Game::Game() :
	m_window("GFX Coursework", {1280, 720}),                 // Create window
	m_viewport(m_window.size()),                             // Create viewport
	m_camera({-30, 10, 20}, {-10,5,0}),                      // Create camera
	m_shader("res/shaders/textured"),                        // Create shader
	m_streetModel(m_shader, "res/models/street/street.obj"), // Create street model
	m_houseModel(m_shader, "res/models/house/house.obj")     // Create house model
{
	// Enable vertical synchronisation
	m_window.verticalSync(true);

	// Set up OpenGL
	glClearColor(0.4f, 0.6f, 0.9f, 1.0f);
	glEnable(GL_DEPTH_TEST);
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

	// Draw the street model
	mat4 streetTransform = {};
	streetTransform = rotate(streetTransform, radians(270.f), {0,1,0});
	streetTransform = scale(streetTransform, {-1,1,1});
	m_streetModel.draw(streetTransform, m_camera.view(), m_viewport.projection());

	// Draw the house model
	mat4 houseTransform = {};
	houseTransform = translate(houseTransform, {7.5f, 0, -20});
	houseTransform = rotate(houseTransform, radians(180.f), {0,1,0});
	houseTransform = scale(houseTransform, vec3(0.1f));
	m_houseModel.draw(houseTransform, m_camera.view(), m_viewport.projection());

	// Swap front and back buffers
	m_window.swapBuffers();
}
