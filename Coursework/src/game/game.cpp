#include "game.hpp"

#include <glad/glad.h>
#include <chrono>

Game::Game() :
	m_window("GFX Coursework", {1280, 720}),  // Create window
	m_viewport(m_window.size()),              // Create viewport
	m_camera({-15, 3, 5}, {-5, 3, -5}),       // Create camera
	m_shaders({
		make_shared<Program>("res/shaders/colored"),
		make_shared<Program>("res/shaders/compound/colored-textured"),
		make_shared<Program>("res/shaders/textured"),
		make_shared<Program>("res/shaders/compound/textured-lit"),
		make_shared<Program>("res/shaders/lit"),
		make_shared<Program>("res/shaders/toon")
	}),
	m_currentShader(3),
	m_house(make_shared<Model>(m_shaders[3], "res/models/house/house.obj"), {{3.25f, 0, -10}, vec3(0.05f), {{180}}}, m_viewport, m_camera),
	m_street(make_shared<Model>(m_shaders[3], "res/models/street/street.obj"), {{}, {-0.5f, 0.5f, 0.5f}, {{270}}}, m_viewport, m_camera),
	m_building1(make_shared<Model>(m_shaders[3], "res/models/buildings/building12.obj"), {{-3.25f, 0, -11}}, m_viewport, m_camera),
	m_building2(make_shared<Model>(m_shaders[3], "res/models/buildings/building07.obj"), {{-13.25f, 0, -13.25f}}, m_viewport, m_camera),
	m_building3(make_shared<Model>(m_shaders[3], "res/models/buildings/building03.obj"), {{{22.5f, 0, -9}}, {{22.5f, 0, -27}}}, m_viewport, m_camera),
	m_moonLight({0, -1, 0}, vec3(0), {0, 0, 0.2f}),
	m_lampModel(make_shared<Model>(m_shaders[3], "res/models/lamp/lamp.obj")),
	m_streetlights({
		{m_lampModel, {{ 4.5f, 0, -4.25f}, {1, 2, 1}, {{90}}}, m_viewport, m_camera},
		{m_lampModel, {{-1.5f, 0, -4.25f}, {1, 2, 1}, {{90}}}, m_viewport, m_camera},
		{m_lampModel, {{-7.5f, 0, -4.25f}, {1, 2, 1}, {{90}}}, m_viewport, m_camera},
		{m_lampModel, {{-13.f, 0, -4.25f}, {1, 2, 1}, {{90}}}, m_viewport, m_camera},
		{m_lampModel, {{ 10.f, 0, -6.25f}, {1, 2, 1}, {{180}}}, m_viewport, m_camera, {0.05f, 5.75f, 0}}
	}),
	m_policeCar(make_shared<Model>(m_shaders[3], "res/models/policecar/policecar.obj"), {{-20.f, 0.05f, -2}, vec3(0.0015f)}, m_viewport, m_camera)
{
	// Enable vertical synchronisation
	m_window.verticalSync(true);

	// Set up OpenGL
	glEnable(GL_DEPTH_TEST);

	// Set up shader
	m_shaders[m_currentShader]->bind();
	m_shaders[m_currentShader]->uniform("ambientLight", {0.25f, 0.25f, 0.35f});
	m_shaders[m_currentShader]->unbind();

	// Add street lights
	for (Streetlight& light : m_streetlights)
	{
		m_pointLights.push_back(&light.pointLight);
		m_spotLights.push_back(&light.spotLight);
	}

	// Add police car headlights
	for (Headlight& light : m_policeCar.headlights)
	{
		m_pointLights.push_back(&light.pointLight);
		m_spotLights.push_back(&light.spotLight);
	}

	// Add police car taillights
	for (Taillight& light : m_policeCar.taillights)
	{
		m_pointLights.push_back(&light.pointLight);
		m_spotLights.push_back(&light.spotLight);
	}
}

void Game::run()
{
	// Initialise previous time
	int prevTime = m_window.ticks();

	while (!m_window.shouldClose())
	{
		// Calculate elapsed time
		int currentTime = m_window.ticks();
		int elapsedTime = currentTime - prevTime;

		// Update and render
		update(elapsedTime);
		render(elapsedTime);

		// Set previous time
		prevTime = currentTime;
	}
}

void Game::update(int elapsedTime)
{
	// Process window events
	m_window.processEvents();

	// Process input events
	m_input.processEvents(m_window.events());

	// Check input
	if (m_input.keyJustReleased(SDLK_ESCAPE))
		m_window.close();

	if (m_input.keyJustReleased(SDLK_SPACE) ||
		m_input.keyJustReleased(SDLK_RETURN))
	{
		setShaders(m_currentShader + 1);
	}

	if (m_input.keyJustReleased(SDLK_1)) setShaders(0);
	if (m_input.keyJustReleased(SDLK_2)) setShaders(1);
	if (m_input.keyJustReleased(SDLK_3)) setShaders(2);
	if (m_input.keyJustReleased(SDLK_4)) setShaders(3);
	if (m_input.keyJustReleased(SDLK_5)) setShaders(4);
	if (m_input.keyJustReleased(SDLK_6)) setShaders(5);

	// Update police car
	m_policeCar.update(elapsedTime);
}

void Game::render(int elapsedTime)
{
	// Clear the back buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw the house model
	m_house.draw(m_directionalLights, m_pointLights, m_spotLights);

	// Draw the street model
	m_street.draw(m_directionalLights, m_pointLights, m_spotLights);

	// Draw the police car model
	m_policeCar.model->draw(m_policeCar.transform.model(), m_camera.view(), m_viewport.projection(), m_directionalLights, m_pointLights, m_spotLights);

	// Draw the building model 1
	m_building1.draw(m_directionalLights, m_pointLights, m_spotLights);

	// Draw the building model 2
	m_building2.draw(m_directionalLights, m_pointLights, m_spotLights);

	// Draw the building model 3
	m_building3.draw(m_directionalLights, m_pointLights, m_spotLights);

	// Draw the lamp model
	for (Streetlight& light : m_streetlights)
		light.model->draw(light.transform.model(), m_camera.view(), m_viewport.projection(), m_directionalLights, m_pointLights, m_spotLights);

	// Swap front and back buffers
	m_window.swapBuffers();
}

void Game::setShaders(int shaderNbr)
{
	m_currentShader = shaderNbr;
	while (m_currentShader >= m_shaders.size())
		m_currentShader -= (int)m_shaders.size();

	m_house.model->shader(m_shaders[m_currentShader]);
	m_street.model->shader(m_shaders[m_currentShader]);
	m_policeCar.model->shader(m_shaders[m_currentShader]);
	m_building1.model->shader(m_shaders[m_currentShader]);
	m_building2.model->shader(m_shaders[m_currentShader]);
	m_building3.model->shader(m_shaders[m_currentShader]);
	for (Streetlight& light : m_streetlights)
		light.model->shader(m_shaders[m_currentShader]);
}
