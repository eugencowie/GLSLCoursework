#pragma once

#include "../engine/window.hpp"
#include "../engine/input.hpp"
#include "../engine/program.inl"
#include "../engine/vertex_array.inl"
#include "../engine/buffer.inl"

class Game
{
public:
	Game();
	void run();

private:
	void update();
	void render();

	Window m_window;
	Input m_input;

	Program m_shader;

	VertexArray m_vertexArray;
	Buffer m_vertexBuffer;
	Buffer m_elementBuffer;
	GLsizei m_drawCount;
};
