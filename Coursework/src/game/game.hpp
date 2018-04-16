#pragma once

#include "../engine/window.hpp"
#include "../engine/input.hpp"
#include "../engine/viewport.inl"
#include "../engine/camera.inl"
#include "../engine/program.inl"
#include "../engine/model.hpp"
#include "../engine/transform.inl"
#include "../engine/light.inl"

struct Streetlight
{
	shared_ptr<Model> model;
	Transform transform;
	PointLight pointLight;
	SpotLight spotLight;

	Streetlight(shared_ptr<Model> model, Transform transform, vec3 lightOffset={0, 5.75f, -0.05f}) :
		model(model),
		transform(transform),
		pointLight({transform.position() + lightOffset}, 0.7f, 1.8f, 1, vec3(0), {1, 1, 0.5f}),
		spotLight({transform.position() + lightOffset}, {0, -1, 0}, cos(radians(27.5f)), cos(radians(35.f)), 0.045f, 0.0075f, 1, vec3(0), {1, 1, 0.5f})
	{
	}
};

class Game
{
public:
	Game();
	void run();

private:
	void update(int elapsedTime);
	void render(int elapsedTime);

	Window m_window;
	Input m_input;

	Viewport m_viewport;
	Camera m_camera;

	Program m_shader;
	Model m_houseModel;
	Model m_streetModel;
	Model m_policecarModel;
	Model m_building1Model;
	Model m_building2Model;
	Model m_building3Model;
	shared_ptr<Model> m_lampModel;

	Transform m_houseTransform;
	Transform m_streetTransform;
	Transform m_policecarTransform;
	Transform m_building1Transform;
	Transform m_building2Transform;
	Transform m_building3Transform1;
	Transform m_building3Transform2;

	DirectionalLight m_moonLight;
	vector<Streetlight> m_streetlights;

	vector<DirectionalLight> m_directionalLights;
	vector<PointLight> m_pointLights;
	vector<SpotLight> m_spotLights;
};
