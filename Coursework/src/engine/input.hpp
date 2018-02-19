#pragma once

#include <glm/glm.hpp>
#include <SDL.h>
#include <vector>
#include <map>

using namespace std;
using namespace glm;

class Input
{
public:
	void processEvents(const vector<SDL_Event>& events);

	bool keyDown(SDL_Keycode key)
	{
		// Check if key is down
		return m_keys[key];
	}

	bool wasKeyDown(SDL_Keycode key)
	{
		// Check if key was down
		return m_prevKeys[key];
	}

	bool mouseDown(Uint8 button)
	{
		// Check if mouse button is down
		return m_mouse[button];
	}

	bool wasMouseDown(Uint8 button)
	{
		// Check if mouse button was down
		return m_prevMouse[button];
	}

	bool keyJustPressed(SDL_Keycode key)
	{
		// Check if key has just been pressed
		return keyDown(key) && !wasKeyDown(key);
	}

	bool keyJustReleased(SDL_Keycode key)
	{
		// Check if key has just been released
		return !keyDown(key) && wasKeyDown(key);
	}

	bool mouseJustPressed(Uint8 button)
	{
		// Check if mouse button has just been pressed
		return mouseDown(button) && !wasMouseDown(button);
	}

	bool mouseJustReleased(Uint8 button)
	{
		// Check if mouse button has just been released
		return !mouseDown(button) && wasMouseDown(button);
	}

	ivec2 mousePos() const
	{
		// Get current mouse position
		return m_mousePos;
	}

private:
	map<SDL_Keycode, bool> m_keys;
	map<SDL_Keycode, bool> m_prevKeys;
	map<Uint8, bool> m_mouse;
	map<Uint8, bool> m_prevMouse;
	ivec2 m_mousePos;
	ivec2 m_prevMousePos;
};
