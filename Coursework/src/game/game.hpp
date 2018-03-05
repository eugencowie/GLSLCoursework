#pragma once

#include "../engine/window.hpp"
#include "../engine/input.hpp"
#include "../engine/viewport.inl"
#include "../engine/camera.inl"
#include "../engine/program.inl"
#include "../engine/model.hpp"

#include <glm/glm.hpp>

using namespace glm;

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
	Model m_lampModel;
	Model m_houseModel;
	Model m_building1Model;
	Model m_building2Model;
	Model m_building3Model;

	mat4 m_streetTransform;
	mat4 m_lampTransform1;
	mat4 m_lampTransform2;
	mat4 m_lampTransform3;
	mat4 m_houseTransform;
	mat4 m_building1Transform;
	mat4 m_building2Transform;
	mat4 m_building3Transform1;
	mat4 m_building3Transform2;
};
