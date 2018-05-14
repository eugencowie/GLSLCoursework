#include "game.hpp"
#include <glad/glad.h>
#include <chrono>

Game::Game() :
	m_window("GFX Coursework", {1280, 720}),  // Create window
	m_viewport(m_window.size()),              // Create viewport
	m_camera({-15, 3, 5}, {-5, 3, -5}),       // Create camera
	m_shaders({
		make_shared<Program>("res/shaders/compound/textured+lit"),     // Load textured+lit shader
		make_shared<Program>("res/shaders/compound/textured+toon"),    // Load textured+toon shader
		make_shared<Program>("res/shaders/toon"),                      // Load toon shader
		make_shared<Program>("res/shaders/lit"),                       // Load lit shader
		make_shared<Program>("res/shaders/colored"),                   // Load colored shader
		make_shared<Program>("res/shaders/compound/colored+textured"), // Load colored+textured shader
		make_shared<Program>("res/shaders/textured")                   // Load textured shader
	}),
	m_objects({
		make_shared<InstancedGameObject>(make_shared<Model>(m_shaders[0], "res/models/buildings/building03.obj"), vector<Transform>{{{22.5f, 0, -9}}, {{22.5f, 0, -27}}}, m_viewport, m_camera),
		make_shared<GameObject>(make_shared<Model>(m_shaders[0], "res/models/street/street.obj"), Transform{{}, {-0.5f, 0.5f, 0.5f}, {{270}}}, m_viewport, m_camera)
	}),
	m_currentShader(m_shaders.size()), // Set initial shader number
	m_house(make_shared<Model>(m_shaders[0], "res/models/house/house.obj"), {{3.25f, 0, -10}, vec3(0.05f), {{180}}}, m_viewport, m_camera),
	m_building1(make_shared<Model>(m_shaders[0], "res/models/buildings/building12.obj"), {{-3.25f, 0, -11}}, m_viewport, m_camera),
	m_building2(make_shared<Model>(m_shaders[0], "res/models/buildings/building07.obj"), {{-13.25f, 0, -13.25f}}, m_viewport, m_camera),
	m_moonLight({0, -1, 0}, vec3(0), {0, 0, 0.2f}),
	m_lampModel(make_shared<Model>(m_shaders[0], "res/models/lamp/lamp.obj")),
	m_streetlights({
		{m_lampModel, {{ 4.5f, 0, -4.25f}, {1, 2, 1}, {{90}}}, m_viewport, m_camera},
		{m_lampModel, {{-1.5f, 0, -4.25f}, {1, 2, 1}, {{90}}}, m_viewport, m_camera},
		{m_lampModel, {{-7.5f, 0, -4.25f}, {1, 2, 1}, {{90}}}, m_viewport, m_camera},
		{m_lampModel, {{-13.f, 0, -4.25f}, {1, 2, 1}, {{90}}}, m_viewport, m_camera},
		{m_lampModel, {{ 10.f, 0, -6.25f}, {1, 2, 1}, {{180}}}, m_viewport, m_camera, {0.05f, 5.75f, 0}}
	}),
	m_policeCar(make_shared<Model>(m_shaders[0], "res/models/policecar/policecar.obj"), {{-20.f, 0.05f, -2}, vec3(0.0015f)}, m_viewport, m_camera)
{
	// Enable vertical synchronisation
	m_window.verticalSync(true);

	// Set up OpenGL
	glEnable(GL_DEPTH_TEST);

	// Set up shaders
	for (shared_ptr<Program> shader : m_shaders)
	{
		shader->bind();
		shader->uniform("ambientLight", {0.25f, 0.25f, 0.35f});
		shader->unbind();
	}

	// Add street lights
	for (Streetlight& light : m_streetlights)
	{
		m_lights.push_back(&light.pointLight);
		m_lights.push_back(&light.spotLight);
	}

	// Add police car headlights
	for (Headlight& light : m_policeCar.headlights)
	{
		m_lights.push_back(&light.pointLight);
		m_lights.push_back(&light.spotLight);
	}

	// Add police car taillights
	for (Taillight& light : m_policeCar.taillights)
	{
		m_lights.push_back(&light.pointLight);
		m_lights.push_back(&light.spotLight);
	}

	m_lights.push_back(&m_moonLight);

	// Set initial shader mix
	mixShaders();
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
		nextShader();
	}

	// Update police car
	m_policeCar.update(elapsedTime);

	// Update timer
	m_timer += elapsedTime;
	if (m_timer > 2000)
	{
		nextShader();
		m_timer = 0;
	}
}

void Game::render(int elapsedTime)
{
	// Clear the back buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw the house model
	m_house.draw(m_lights);

	// Draw the police car model
	m_policeCar.model->draw(m_policeCar.transform.model(), m_camera.view(), m_viewport.projection(), m_lights);

	// Draw the building model 1
	m_building1.draw(m_lights);

	// Draw the building model 2
	m_building2.draw(m_lights);

	// Draw the game objects
	for (GameObjectPtr object : m_objects)
		object->draw(m_lights);

	// Draw the lamp model
	for (Streetlight& light : m_streetlights)
		light.model->draw(light.transform.model(), m_camera.view(), m_viewport.projection(), m_lights);

	// Swap front and back buffers
	m_window.swapBuffers();
}

void Game::nextShader()
{
	// Increase current shader number
	m_currentShader += 1;

	// Mix shaders if we have reached the end of the list
	// Return to beginning of list if we have gone past the end
	// Otherwise just apply the new shader
	if      (m_currentShader == m_shaders.size()) mixShaders();
	else if (m_currentShader >= m_shaders.size()) applyShader(m_currentShader = 0);
	else                                          applyShader(m_currentShader);
}

void Game::applyShader(int shaderNbr)
{
	m_house.model->shader(m_shaders[shaderNbr]);
	m_policeCar.model->shader(m_shaders[shaderNbr]);
	m_building1.model->shader(m_shaders[shaderNbr]);
	m_building2.model->shader(m_shaders[shaderNbr]);
	for (GameObjectPtr object : m_objects)
		object->model->shader(m_shaders[shaderNbr]);
	for (Streetlight& light : m_streetlights)
		light.model->shader(m_shaders[shaderNbr]);
}

void Game::mixShaders()
{
	setShader(0);

	for (GameObjectPtr object : m_objects) {
		object->draw(m_lights);
		setShader(m_currentShader + 1);
	}
	
	m_house.model->shader(m_shaders[m_currentShader]);
	setShader(m_currentShader + 1);
	
	for (Streetlight& light : m_streetlights)
		light.model->shader(m_shaders[m_currentShader]);
	setShader(m_currentShader + 1);
	
	m_policeCar.model->shader(m_shaders[m_currentShader]);
	setShader(m_currentShader + 1);
	
	m_building1.model->shader(m_shaders[m_currentShader]);
	setShader(m_currentShader + 1);
	
	m_building2.model->shader(m_shaders[m_currentShader]);
	setShader(m_currentShader + 1);

	m_currentShader = m_shaders.size();
}

void Game::setShader(int shaderNbr)
{
	m_currentShader = shaderNbr;
	if (m_currentShader >= m_shaders.size()) m_currentShader = 0;
}
