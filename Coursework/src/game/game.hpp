#pragma once

#include "../engine/window.hpp"
#include "../engine/input.hpp"
#include "../engine/viewport.inl"
#include "../engine/camera.inl"
#include "../engine/program.inl"
#include "../engine/model.hpp"
#include "../engine/transform.inl"
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
	void setShaders(int shaderNbr);

	Window m_window;
	Input m_input;

	Viewport m_viewport;
	Camera m_camera;

	Program m_coloredShader;
	Program m_texturedShader;
	Program m_litShader;
	Program m_coloredTexturedShader;
	Program m_texturedLitShader;
	vector<Program*> m_shaders;
	int m_currentShader;

	Model m_houseModel;
	Model m_streetModel;
	Model m_building1Model;
	Model m_building2Model;
	Model m_building3Model;
	shared_ptr<Model> m_lampModel;

	Transform m_houseTransform;
	Transform m_streetTransform;
	Transform m_building1Transform;
	Transform m_building2Transform;
	Transform m_building3Transform1;
	Transform m_building3Transform2;

	DirectionalLight m_moonLight;
	vector<Streetlight> m_streetlights;

	Car m_policeCar;

	vector<DirectionalLight*> m_directionalLights;
	vector<PointLight*> m_pointLights;
	vector<SpotLight*> m_spotLights;
};
