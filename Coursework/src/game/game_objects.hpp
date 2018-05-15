#pragma once

#include "../engine/model.hpp"
#include "../engine/transform.inl"
#include "../engine/viewport.inl"
#include "../engine/camera.inl"
#include "../engine/light.inl"
#include <glm/glm.hpp>
#include <memory>

using namespace std;

typedef shared_ptr<struct GameObject> GameObjectPtr;

struct GameObject
{
	ModelPtr model;
	Transform transform;
	Viewport& viewport;
	Camera& camera;

	GameObject(ModelPtr model, Transform transform, Viewport& viewport, Camera& camera) :
		model(model), transform(transform), viewport(viewport), camera(camera)
	{
	}

	virtual void update(int elapsedTime) { }

	virtual void draw(const vector<ILightPtr>& lights)
	{
		// Draw the model
		model->draw(transform.model(), camera.view(), viewport.projection(), lights);
	}
};

struct InstancedGameObject : public GameObject
{
	vector<Transform> transforms;

	InstancedGameObject(ModelPtr model, vector<Transform> transforms, Viewport& viewport, Camera& camera) :
		GameObject(model, transforms[0], viewport, camera),
		transforms(transforms)
	{
	}

	virtual void draw(const vector<ILightPtr>& lights) override
	{
		for (Transform& t : transforms)
		{
			// Use this transform
			transform = t;

			// Draw the model
			GameObject::draw(lights);
		}
	}
};

struct Streetlight : public GameObject
{
	PointLightPtr pointLight;
	SpotLightPtr spotLight;

	Streetlight(ModelPtr model, Transform transform, Viewport& viewport, Camera& camera, vec3 lightOffset={0, 5.75f, -0.05f}) :
		GameObject(model, transform, viewport, camera),
		pointLight(make_shared<PointLight>(transform.position() + lightOffset, 0.7f, 1.8f, 1.f, vec3(0), vec3{1, 1, 0.5f})),
		spotLight(make_shared<SpotLight>(transform.position() + lightOffset, vec3{0, -1, 0}, cos(radians(27.5f)), cos(radians(35.f)), 0.045f, 0.0075f, 1.f, vec3(0), vec3{1, 1, 0.5f}))
	{
	}
};

struct Carlight
{
	GameObject* parent;
	vec3 pointLightOffset;
	vec3 spotLightOffset;
	PointLightPtr pointLight;
	SpotLightPtr spotLight;

	Carlight(GameObject* parent, vec3 pointLightOffset, vec3 spotLightOffset, PointLightPtr pointLight, SpotLightPtr spotLight) :
		parent(parent), pointLightOffset(pointLightOffset), spotLightOffset(spotLightOffset), pointLight(pointLight), spotLight(spotLight)
	{
	}

	Carlight(GameObject* parent, vec3 offset, PointLightPtr pointLight, SpotLightPtr spotLight) :
		Carlight(parent, offset, offset, pointLight, spotLight)
	{
	}

	void update()
	{
		pointLight->position = parent->transform.position() + pointLightOffset;
		spotLight->position = parent->transform.position() + spotLightOffset;
	}
};

struct Headlight : public Carlight
{
	Headlight(GameObject* parent, vec3 offset) : Carlight(
		parent,
		offset,
		make_shared<PointLight>(offset, 0.07f, 0.017f, 1.f, vec3(0), vec3(1), vec3(0)),
		make_shared<SpotLight>(offset, vec3{1, 0, 0}, cos(radians(12.5f)), cos(radians(17.5f)), 0.045f, 0.0075f, 1.f, vec3(0), vec3(1), vec3(0)))
	{
	}
};

struct Taillight : public Carlight
{
	Taillight(GameObject* parent, vec3 offset) : Carlight(
		parent,
		offset,
		offset + vec3(2, 0, 0),
		make_shared<PointLight>(offset, 0.1525f, 0.45f, 1.f, vec3(0), vec3(1, 0, 0), vec3(0)),
		make_shared<SpotLight>(offset, vec3{0, -0.6f, 1}, cos(radians(12.5f)), cos(radians(17.5f)), 0.045f, 0.0075f, 1.f, vec3(0), vec3(1, 0, 0), vec3(0)))
	{
	}
};

struct Car : public GameObject
{
	vector<Carlight> lights;
	bool turned;

	Car(ModelPtr model, Transform transform, Viewport& viewport, Camera& camera) :
		GameObject(model, transform, viewport, camera),
		lights({
			Headlight{this, {9, 1, -1}}, Headlight{this, {9, 1, 1}},
			Taillight{this, {0, 1, -1}}, Taillight{this, {0, 1, 1}}
		}),
		turned(false)
	{
	}

	virtual void update(int elapsedTime) override;
};
