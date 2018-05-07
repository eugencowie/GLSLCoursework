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
		pointLight(transform.position() + lightOffset, 0.7f, 1.8f, 1, vec3(0), {1, 1, 0.5f}),
		spotLight(transform.position() + lightOffset, {0, -1, 0}, cos(radians(27.5f)), cos(radians(35.f)), 0.045f, 0.0075f, 1, vec3(0), {1, 1, 0.5f})
	{
	}
};

struct Headlight
{
	vec3 offset;
	PointLight pointLight;
	SpotLight spotLight;

	Headlight(vec3 offset) :
		offset(offset),
		pointLight(offset, 0.07f, 0.017f, 1, vec3(0), vec3(1), vec3(0)),
		spotLight(offset, {1, 0, 0}, cos(radians(12.5f)), cos(radians(17.5f)), 0.045f, 0.0075f, 1, vec3(0), vec3(1), vec3(0))
	{
	}

	void update(Transform parent)
	{
		pointLight.position = parent.position() + offset;
		spotLight.position = parent.position() + offset;
	}
};

struct Taillight
{
	vec3 offset;
	PointLight pointLight;
	SpotLight spotLight;

	Taillight(vec3 offset) :
		offset(offset),
		pointLight(offset, 0.1525f, 0.45f, 1, vec3(0), vec3(1,0,0), vec3(0)),
		spotLight(offset, {0, -0.6f, 1}, cos(radians(12.5f)), cos(radians(17.5f)), 0.045f, 0.0075f, 1, vec3(0), vec3(1, 0, 0), vec3(0))
	{
	}

	void update(Transform parent)
	{
		pointLight.position = parent.position() + offset;
		spotLight.position = parent.position() + offset + vec3(2,0,0);
	}
};

struct Car
{
	shared_ptr<Model> model;
	Transform transform;
	vector<Headlight> headlights;
	vector<Taillight> taillights;
	bool turned;

	Car(Program* shader) :
		model(make_shared<Model>(shader, "res/models/policecar/policecar.obj")),
		transform({-20.f, 0.05f, -2 }, vec3(0.0015f)),
		headlights({{{9, 1, -1}}, {{9, 1, 1}}}),
		taillights({{{0, 1, -1}}, {{0, 1, 1}}}),
		turned(false)
	{
	}

	void update(int elapsedTime)
	{
		if (turned)
			transform.move({0, 0, -0.005f * elapsedTime});
		else
			transform.move({0.005f * elapsedTime, 0, 0});

		if (!turned && transform.position().x > 7)
		{
			turned = true;
			transform.move({5, 0.05f, 0});
			transform.rotations({{90}});
			for (Headlight& light : headlights)
			{
				light.offset = vec3(-light.offset.z, light.offset.y, -light.offset.x);
				light.spotLight.direction = vec3(-light.spotLight.direction.z, light.spotLight.direction.y, -light.spotLight.direction.x);
			}
			for (Taillight& light : taillights)
			{
				light.offset = vec3(-light.offset.z, light.offset.y, -light.offset.x);
				light.spotLight.direction = vec3(-light.spotLight.direction.z, light.spotLight.direction.y, -light.spotLight.direction.x);
			}
		}
		else if (turned && transform.position().z < -20)
		{
			turned = false;
			transform.position({-20.f, 0.05f, -2});
			transform.rotations({});
			for (Headlight& light : headlights)
			{
				light.offset = vec3(-light.offset.z, light.offset.y, -light.offset.x);
				light.spotLight.direction = vec3(-light.spotLight.direction.z, light.spotLight.direction.y, -light.spotLight.direction.x);
			}
			for (Taillight& light : taillights)
			{
				light.offset = vec3(-light.offset.z, light.offset.y, -light.offset.x);
				light.spotLight.direction = vec3(-light.spotLight.direction.z, light.spotLight.direction.y, -light.spotLight.direction.x);
			}
		}

		for (Headlight& light : headlights)
			light.update(transform);

		for (Taillight& light : taillights)
			light.update(transform);
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

	Program m_coloredShader;
	Program m_texturedShader;
	Program m_litShader;
	Program m_coloredTexturedShader;
	Program m_texturedLitShader;
	vector<Program*> m_shaders;
	unsigned int m_currentShader;

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
