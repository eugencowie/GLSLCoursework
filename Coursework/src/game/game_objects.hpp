#pragma once

#include "../engine/model.hpp"
#include "../engine/transform.inl"
#include "../engine/viewport.inl"
#include "../engine/camera.inl"
#include "../engine/light.inl"

struct GameObject
{
	shared_ptr<Model> model;
	Transform transform;
	Viewport& viewport;
	Camera& camera;

	GameObject(shared_ptr<Model> model, Transform transform, Viewport& viewport, Camera& camera) :
		model(model), transform(transform), viewport(viewport), camera(camera)
	{
	}

	void draw()
	{
		model->draw(transform.model(), camera.view(), viewport.projection());
	}
};

struct Streetlight : public GameObject
{
	PointLight pointLight;
	SpotLight spotLight;

	Streetlight(shared_ptr<Model> model, Transform transform, Viewport& viewport, Camera& camera, vec3 lightOffset={0, 5.75f, -0.05f}) :
		GameObject(model, transform, viewport, camera),
		pointLight(transform.position() + lightOffset, 0.7f, 1.8f, 1, vec3(0), { 1, 1, 0.5f }),
		spotLight(transform.position() + lightOffset, {0, -1, 0}, cos(radians(27.5f)), cos(radians(35.f)), 0.045f, 0.0075f, 1, vec3(0), {1, 1, 0.5f})
	{
	}
};

struct Headlight
{
	GameObject* parent;
	vec3 offset;
	PointLight pointLight;
	SpotLight spotLight;

	Headlight(GameObject* parent, vec3 offset) :
		parent(parent),
		offset(offset),
		pointLight(offset, 0.07f, 0.017f, 1, vec3(0), vec3(1), vec3(0)),
		spotLight(offset, {1, 0, 0}, cos(radians(12.5f)), cos(radians(17.5f)), 0.045f, 0.0075f, 1, vec3(0), vec3(1), vec3(0))
	{
	}

	void update()
	{
		pointLight.position = parent->transform.position() + offset;
		spotLight.position = parent->transform.position() + offset;
	}
};

struct Taillight
{
	GameObject* parent;
	vec3 offset;
	PointLight pointLight;
	SpotLight spotLight;

	Taillight(GameObject* parent, vec3 offset) :
		parent(parent),
		offset(offset),
		pointLight(offset, 0.1525f, 0.45f, 1, vec3(0), vec3(1, 0, 0), vec3(0)),
		spotLight(offset, { 0, -0.6f, 1 }, cos(radians(12.5f)), cos(radians(17.5f)), 0.045f, 0.0075f, 1, vec3(0), vec3(1, 0, 0), vec3(0))
	{
	}

	void update()
	{
		pointLight.position = parent->transform.position() + offset;
		spotLight.position = parent->transform.position() + offset + vec3(2, 0, 0);
	}
};

struct Car : public GameObject
{
	vector<Headlight> headlights;
	vector<Taillight> taillights;
	bool turned;

	Car(shared_ptr<Model> model, Transform transform, Viewport& viewport, Camera& camera) :
		GameObject(model, transform, viewport, camera),
		headlights({{this, {9, 1, -1}}, {this, {9, 1, 1}}}),
		taillights({{this, {0, 1, -1}}, {this, {0, 1, 1}}}),
		turned(false)
	{
	}

	void update(int elapsedTime)
	{
		if (turned)
			transform.move({ 0, 0, -0.005f * elapsedTime });
		else
			transform.move({ 0.005f * elapsedTime, 0, 0 });

		if (!turned && transform.position().x > 7)
		{
			turned = true;
			transform.move({ 5, 0.05f, 0 });
			transform.rotations({ { 90 } });
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
			transform.position({ -20.f, 0.05f, -2 });
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
			light.update();

		for (Taillight& light : taillights)
			light.update();
	}
};
