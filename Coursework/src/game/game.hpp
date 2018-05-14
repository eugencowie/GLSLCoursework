#pragma once

#include "../engine/window.hpp"
#include "../engine/input.hpp"
#include "../engine/viewport.inl"
#include "../engine/camera.inl"
#include "../engine/program.inl"
#include "../engine/light.inl"
#include "../engine/model.hpp"
#include "game_objects.hpp"

class Game
{
public:
	Game();
	void run();

private:
	void update(int elapsedTime);
	void render(int elapsedTime);
	void nextShader();
	void applyShader(int shaderNbr);
	void mixShaders();
	void setShader(int shaderNbr);

	Window m_window;
	Input m_input;
	Viewport m_viewport;
	Camera m_camera;

	vector<ProgramPtr> m_shaders;
	vector<ILightPtr> m_lights;

	shared_ptr<Model> m_lampModel;
	vector<GameObjectPtr> m_objects;

	int m_currentShader;
	int m_timer;
	bool m_paused;
};
