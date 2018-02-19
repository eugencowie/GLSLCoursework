#pragma once

#include "../engine/window.hpp"

class Game
{
public:
	Game();
	void run();

private:
	void update();
	void render();

	Window m_window;
};
