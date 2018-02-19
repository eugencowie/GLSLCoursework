#pragma once

#include "../engine/window.hpp"
#include "../engine/input.hpp"

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
};
