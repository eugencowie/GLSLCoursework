#pragma once

#include <SDL.h>
#include <string>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class Window
{
public:
	Window(const string& title, ivec2 size);
	~Window();
	void processEvents();

	void swapBuffers()
	{
		// Swap front and back buffers
		SDL_GL_SwapWindow(m_window);
	}

	void verticalSync(bool vsync)
	{
		// Enable/disable vertical synchronisation
		SDL_GL_SetSwapInterval(vsync ? 1 : 0);
	}

	bool shouldClose() const
	{
		// Get whether the window should close
		return m_shouldClose;
	}

private:
	SDL_Window* m_window;
	bool m_shouldClose;

	// Rule of five
	Window(Window&&) = delete;
	Window(const Window&) = delete;
	Window& operator=(Window&&) = delete;
	Window& operator=(const Window&) = delete;
};
