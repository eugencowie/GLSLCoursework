#pragma once

#include "../engine/window.hpp"
#include "../engine/input.hpp"
#include "../engine/shader.inl"

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

	Shader m_vertexShader;
	Shader m_fragmentShader;
};
