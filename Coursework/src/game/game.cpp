#include "game.hpp"

#include <glad/glad.h>

Game::Game() :
	m_window("GFX Coursework", {1280, 720}), // Create window
	m_viewport(m_window.size()),             // Create viewport
	m_camera({-15, 3, 5}, {-5, 3, -5}),      // Create camera
	m_shader("res/shaders/textured"),        // Create shader
	m_streetModel(m_shader, "res/models/street/street.obj"), // Create street model
	m_lampModel(m_shader, "res/models/lamp/lamp.obj"),       // Create lamp model
	m_houseModel(m_shader, "res/models/house/house.obj"),    // Create house model
	m_building1Model(m_shader, "res/models/buildings/building12.obj"), // Create building model 1
	m_building2Model(m_shader, "res/models/buildings/building07.obj"), // Create building model 2
	m_building3Model(m_shader, "res/models/buildings/building03.obj"), // Create building model 3
	m_streetTransform(rotate(radians(270.f), vec3{0,1,0}) * scale(vec3{-0.5f, 0.5f, 0.5f})),
	m_lampTransform1(translate(vec3{-1.5f, 0, -5}) * rotate(radians(90.f), vec3{0,1,0}) * scale(vec3(1, 2, 1))),
	m_lampTransform2(translate(vec3{-7.5f, 0, -5}) * rotate(radians(90.f), vec3{0,1,0}) * scale(vec3(1, 2, 1))),
	m_lampTransform3(translate(vec3{-13, 0, -5}) * rotate(radians(90.f), vec3{0,1,0}) * scale(vec3(1, 2, 1))),
	m_houseTransform(translate(vec3{3.25f, 0, -10}) * rotate(radians(180.f), vec3{0,1,0}) * scale(vec3(0.05f))),
	m_building1Transform(translate(vec3{-3.25f, 0, -11})),
	m_building2Transform(translate(vec3{-13.25f, 0, -13.25f})),
	m_building3Transform1(translate(vec3{22.5f, 0, -9})),
	m_building3Transform2(translate(vec3{22.5f, 0, -27}))
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
	m_streetModel.draw(m_streetTransform, m_camera.view(), m_viewport.projection());

	// Draw the lamp model
	m_lampModel.draw(m_lampTransform1, m_camera.view(), m_viewport.projection());
	m_lampModel.draw(m_lampTransform2, m_camera.view(), m_viewport.projection());
	m_lampModel.draw(m_lampTransform3, m_camera.view(), m_viewport.projection());

	// Draw the house model
	m_houseModel.draw(m_houseTransform, m_camera.view(), m_viewport.projection());

	// Draw the building model 1
	m_building1Model.draw(m_building1Transform, m_camera.view(), m_viewport.projection());

	// Draw the building model 2
	m_building2Model.draw(m_building2Transform, m_camera.view(), m_viewport.projection());

	// Draw the building model 3
	m_building3Model.draw(m_building3Transform1, m_camera.view(), m_viewport.projection());
	m_building3Model.draw(m_building3Transform2, m_camera.view(), m_viewport.projection());

	// Swap front and back buffers
	m_window.swapBuffers();
}
