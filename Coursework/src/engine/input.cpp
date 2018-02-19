#include "input.hpp"

void Input::processEvents(const vector<SDL_Event>& events)
{
	// Set previous values
	m_prevKeys = m_keys;
	m_prevMouse = m_mouse;
	m_prevMousePos = m_mousePos;

	for (auto& e : events)
	{
		switch (e.type)
		{
			case SDL_KEYDOWN:
				// Add key to current key pressed list
				m_keys[e.key.keysym.sym] = true;
				break;

			case SDL_KEYUP:
				// Remove key from current key pressed list
				m_keys[e.key.keysym.sym] = false;
				break;

			case SDL_MOUSEBUTTONDOWN:
				// Add button to current button pressed list
				m_mouse[e.button.button] = true;
				break;

			case SDL_MOUSEBUTTONUP:
				// Remove button from current button pressed list
				m_mouse[e.button.button] = false;
				break;

			case SDL_MOUSEMOTION:
				// Set mouse location
				m_mousePos = {e.motion.x, e.motion.y};
				break;
		}
	}
}
