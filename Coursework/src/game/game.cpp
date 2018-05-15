#include "game.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>

Game::Game() :
	m_window("GFX Coursework", {1280, 720}),  // Create window
	m_viewport(m_window.size()),              // Create viewport
	m_camera({-15, 3, 5}, {-5, 3, -5}),       // Create camera
	m_shaders({                               // Create shaders
		make_shared<Program>("res/shaders/compound/textured+lit"),
		make_shared<Program>("res/shaders/compound/textured+toon"),
		make_shared<Program>("res/shaders/toon"),
		make_shared<Program>("res/shaders/lit"),
		make_shared<Program>("res/shaders/colored"),
		make_shared<Program>("res/shaders/compound/colored+textured"),
		make_shared<Program>("res/shaders/textured")
	}),
	m_lights({                                // Create directional moonlight
		make_shared<DirectionalLight>(vec3{0, -1, 0}, vec3(0), vec3{0, 0, 0.2f})
	}),
	m_objects({                               // Load and position game objects in scene
		make_shared<InstancedGameObject>(make_shared<Model>(m_shaders[0], "res/models/buildings/building03.obj"), vector<Transform>{{{22.5f, 0, -9}}, {{22.5f, 0, -27}}}, m_viewport, m_camera),
		make_shared<GameObject>(make_shared<Model>(m_shaders[0], "res/models/street/street.obj"), Transform{{}, {-0.5f, 0.5f, 0.5f}, {{270}}}, m_viewport, m_camera),
		make_shared<GameObject>(make_shared<Model>(m_shaders[0], "res/models/house/house.obj"), Transform{{3.25f, 0, -10}, vec3(0.05f), {{180}}}, m_viewport, m_camera),
		make_shared<Streetlight>(make_shared<Model>(m_shaders[0], "res/models/lamp/lamp.obj"), Transform{{ 4.5f, 0, -4.25f}, {1, 2, 1}, {{90}}}, m_viewport, m_camera),
		make_shared<Car>(make_shared<Model>(m_shaders[0], "res/models/policecar/policecar.obj"), Transform{{-20.f, 0.05f, -2}, vec3(0.0015f)}, m_viewport, m_camera),
		make_shared<GameObject>(make_shared<Model>(m_shaders[0], "res/models/buildings/building12.obj"), Transform{{-3.25f, 0, -11}}, m_viewport, m_camera),
		make_shared<GameObject>(make_shared<Model>(m_shaders[0], "res/models/buildings/building07.obj"), Transform{{-13.25f, 0, -13.25f}}, m_viewport, m_camera),
		make_shared<Streetlight>(make_shared<Model>(m_shaders[0], "res/models/lamp/lamp.obj"), Transform{{-1.5f, 0, -4.25f}, {1, 2, 1}, {{90}}}, m_viewport, m_camera),
		make_shared<Streetlight>(make_shared<Model>(m_shaders[0], "res/models/lamp/lamp.obj"), Transform{{-7.5f, 0, -4.25f}, {1, 2, 1}, {{90}}}, m_viewport, m_camera),
		make_shared<Streetlight>(make_shared<Model>(m_shaders[0], "res/models/lamp/lamp.obj"), Transform{{-13.f, 0, -4.25f}, {1, 2, 1}, {{90}}}, m_viewport, m_camera),
		make_shared<Streetlight>(make_shared<Model>(m_shaders[0], "res/models/lamp/lamp.obj"), Transform{{ 10.f, 0, -6.25f}, {1, 2, 1}, {{180}}}, m_viewport, m_camera, vec3{0.05f, 5.75f, 0})
	}),
	m_currentShader((int)m_shaders.size())    // Set initial shader number
{
	// Enable vertical synchronisation
	m_window.verticalSync(true);

	// Set up OpenGL
	glEnable(GL_DEPTH_TEST);

	// Set up ambient light
	for (ProgramPtr shader : m_shaders)
	{
		shader->bind();
		shader->uniform("ambientLight", {0.25f, 0.25f, 0.35f});
		shader->unbind();
	}

	// Add streetlights to list of light sources
	for (GameObjectPtr object : m_objects)
	{
		if (auto light = dynamic_pointer_cast<Streetlight>(object))
		{
			m_lights.push_back(light->pointLight);
			m_lights.push_back(light->spotLight);
		}
	}

	// Add car headlights and taillights to list of light sources
	for (GameObjectPtr object : m_objects)
	{
		if (auto car = dynamic_pointer_cast<Car>(object))
		{
			for (Carlight& light : car->lights)
			{
				m_lights.push_back(light.pointLight);
				m_lights.push_back(light.spotLight);
			}
		}
	}

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

	// Close window if escape key is pressed and released
	if (m_input.keyJustReleased(SDLK_ESCAPE))
	{
		m_window.close();
	}

	// Pause/resume automatic time-based shader updates if space key is pressed and released
	if (m_input.keyJustReleased(SDLK_SPACE))
	{
		m_paused = !m_paused;
	}

	// Pause and switch to the previous shader if left arrow key is pressed and released
	if (m_input.keyJustReleased(SDLK_LEFT))
	{
		m_paused = true;
		prevShader();
	}

	// Pause and switch to the next shader if right arrow key is pressed and released
	if (m_input.keyJustReleased(SDLK_RIGHT))
	{
		m_paused = true;
		nextShader();
	}

	// Update game objects
	for (GameObjectPtr object : m_objects)
	{
		object->update(elapsedTime);
	}

	// Update timer
	m_timer += elapsedTime;
	if (!m_paused && m_timer > 2000)
	{
		nextShader();
		m_timer = 0;
	}
}

void Game::render(int elapsedTime)
{
	// Clear the back buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw the game objects
	for (GameObjectPtr object : m_objects)
	{
		object->draw(m_lights);
	}

	// Swap front and back buffers
	m_window.swapBuffers();
}

void Game::mixShaders()
{
	// Start with first shader
	m_currentShader = 0;

	for (GameObjectPtr object : m_objects)
	{
		// Apply current shader to model
		object->model->shader(m_shaders[m_currentShader]);

		// Move on to next shader
		m_currentShader++;
		
		// Reset current shader to start if we have reached the last shader
		if (m_currentShader >= m_shaders.size())
		{
			m_currentShader = 0;
		}
	}

	// Set current shader to special value indicating mixed shaders
	m_currentShader = (int)m_shaders.size();
}

void Game::nextShader()
{
	// Move on to next shader
	m_currentShader++;

	// Mix shaders if we have reached the end of the list
	if (m_currentShader == m_shaders.size())
	{
		mixShaders();
	}

	// Reset current shader to start of list if we have gone past the end of the list
	else if (m_currentShader >= m_shaders.size())
	{
		applyShader(0);
	}

	// Otherwise apply the shader
	else
	{
		applyShader(m_currentShader);
	}
}

void Game::prevShader()
{
	// Return to previous shader
	m_currentShader--;

	// Mix shaders if we have reached the start of the list
	if (m_currentShader < 0)
	{
		mixShaders();
	}

	// Otherwise apply the shader
	else
	{
		applyShader(m_currentShader - 1);
	}
}

void Game::applyShader(int shaderNbr)
{
	// Set current shader
	m_currentShader = shaderNbr;

	for (GameObjectPtr object : m_objects)
	{
		// Apply shader to model
		object->model->shader(m_shaders[m_currentShader]);
	}
}
