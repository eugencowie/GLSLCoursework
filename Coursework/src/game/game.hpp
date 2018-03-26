#pragma once

#include "../engine/window.hpp"
#include "../engine/input.hpp"
#include "../engine/viewport.inl"
#include "../engine/camera.inl"
#include "../engine/program.inl"
#include "../engine/model.hpp"
#include "../engine/transform.inl"
#include "../engine/light.inl"

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

	Transform m_streetTransform;
	Transform m_lampTransform1;
	Transform m_lampTransform2;
	Transform m_lampTransform3;
	Transform m_lampTransform4;
	Transform m_houseTransform;
	Transform m_building1Transform;
	Transform m_building2Transform;
	Transform m_building3Transform1;
	Transform m_building3Transform2;

	DirectionalLight m_moonLight;
	PointLight m_pointLight1;
	PointLight m_pointLight2;
	PointLight m_pointLight3;
	PointLight m_pointLight4;
	SpotLight m_spotLight1;
	SpotLight m_spotLight2;
	SpotLight m_spotLight3;
	SpotLight m_spotLight4;
};
