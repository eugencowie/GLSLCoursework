#include "game.hpp"
#include "../engine/vertex.inl"
#include <glad/glad.h>
#include <vector>

Game::Game() :
	m_window("GFX Coursework", {1280, 720}), // Create window
	m_shader("res/shaders/colored"),         // Create shader
	m_vertexBuffer(GL_ARRAY_BUFFER),         // Create vertex buffer
	m_elementBuffer(GL_ELEMENT_ARRAY_BUFFER) // Create element buffer
{
	// Enable vertical synchronisation
	m_window.verticalSync(true);

	// Set up OpenGL
	glClearColor(0.4f, 0.6f, 0.9f, 1.0f);

	// Set vertices
	vector<Vertex> vertices = {
		{{-0.5f,  0.5f, 0}, {0, 0, 0, 1}}, // Top left
		{{-0.5f, -0.5f, 0}, {1, 0, 0, 1}}, // Bottom left
		{{ 0.5f,  0.5f, 0}, {0, 1, 0, 1}}, // Top right
		{{ 0.5f, -0.5f, 0}, {0, 0, 1, 1}}  // Bottom right
	};

	// Set indices
	vector<uvec3> indices = {
		{0, 1, 2},
		{3, 2, 1}
	};
	m_drawCount = (GLsizei)(indices.size() * 3);

	// Set up VAO
	m_vertexArray.bind();
	
	m_vertexBuffer.bind();
	m_vertexBuffer.data(vertices, GL_STATIC_DRAW);
	m_shader.vertexAttribPointer("vertexPosition", 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	m_shader.vertexAttribPointer("vertexColor", 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	
	m_elementBuffer.bind();
	m_elementBuffer.data(indices, GL_STATIC_DRAW);
	
	m_vertexArray.unbind();
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
	m_shader.bind();
	m_shader.uniform("modelViewProjection", mat4{});
	m_vertexArray.bind();
	m_elementBuffer.bind();
	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, nullptr);
	m_vertexArray.unbind();
	m_shader.unbind();

	// Swap front and back buffers
	m_window.swapBuffers();
}
