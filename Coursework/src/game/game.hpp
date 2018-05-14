#pragma once

#include "../engine/window.hpp"
#include "../engine/input.hpp"
#include "../engine/viewport.inl"
#include "../engine/camera.inl"
#include "../engine/program.inl"
#include "../engine/light.inl"
#include "game_objects.hpp"

class Game
{
public:
	Game();
	void run();

private:
	void update(int elapsedTime);
	void render(int elapsedTime);

	void mixShaders();
	void nextShader();
	void prevShader();
	void applyShader(int shaderNbr);

	Window m_window;
	Input m_input;
	Viewport m_viewport;
	Camera m_camera;

	vector<ProgramPtr> m_shaders;
	vector<ILightPtr> m_lights;
	vector<GameObjectPtr> m_objects;

	int m_currentShader;
	int m_timer;
	bool m_paused;
};
