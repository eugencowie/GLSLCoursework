#pragma once

#include "../engine/window.hpp"
#include "../engine/input.hpp"
#include "../engine/viewport.inl"
#include "../engine/camera.inl"
#include "../engine/program.inl"
#include "../engine/model.hpp"

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

	Viewport m_viewport;
	Camera m_camera;

	Program m_shader;
	Model m_streetModel;
	Model m_houseModel;
	Model m_buildingModel1;
	Model m_buildingModel2;
	Model m_buildingModel3;
};
