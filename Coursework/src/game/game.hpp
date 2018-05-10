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

	GameObject m_house;
	GameObject m_street;
	GameObject m_building1;
	GameObject m_building2;
	InstancedGameObject m_building3;

	DirectionalLight m_moonLight;
	shared_ptr<Model> m_lampModel;
	vector<Streetlight> m_streetlights;

	Car m_policeCar;

	vector<DirectionalLight*> m_directionalLights;
	vector<PointLight*> m_pointLights;
	vector<SpotLight*> m_spotLights;
};
