#pragma once

#include "../engine/window.hpp"

class Game
{
public:
	Game();
	void run();

private:
	Window m_window;
};
