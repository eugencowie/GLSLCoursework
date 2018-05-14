#pragma once

#include "program.inl"
#include <glm/glm.hpp>
#include <string>

using namespace std;
using namespace glm;

enum class LightType { DIRECTIONAL, POINT, SPOT };

struct ILight
{
	virtual ~ILight() { }
	virtual LightType type() = 0;
	virtual void apply(shared_ptr<Program> shader, string name) = 0;
};

struct DirectionalLight : public ILight
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	DirectionalLight(
		vec3 direction = {0, -1, 0},
		vec3 ambient = vec3(0),
		vec3 diffuse = vec3(1),
		vec3 specular = vec3(1)
	) :
		direction(direction),
		ambient(ambient),
		diffuse(diffuse),
		specular(specular)
	{
	}

	virtual LightType type() override
	{
		return LightType::DIRECTIONAL;
	}

	virtual void apply(shared_ptr<Program> shader, string name) override
	{
		shader->uniform(name + ".direction", direction);
		shader->uniform(name + ".ambient",   ambient);
		shader->uniform(name + ".diffuse",   diffuse);
		shader->uniform(name + ".specular",  specular);
	}
};

struct PointLight : public ILight
{
	vec3 position;
	float linear;
	float quadratic;
	float constant;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	PointLight(
		vec3 position = {},
		float linear = 0.7f,
		float quadratic = 1.8f,
		float constant = 1,
		vec3 ambient = vec3(0),
		vec3 diffuse = vec3(1),
		vec3 specular = vec3(1)
	) :
		position(position),
		linear(linear),
		quadratic(quadratic),
		constant(constant),
		ambient(ambient),
		diffuse(diffuse),
		specular(specular)
	{
	}

	virtual LightType type() override
	{
		return LightType::POINT;
	}

	virtual void apply(shared_ptr<Program> shader, string name) override
	{
		shader->uniform(name + ".position",  position);
		shader->uniform(name + ".constant",  constant);
		shader->uniform(name + ".linear",    linear);
		shader->uniform(name + ".quadratic", quadratic);
		shader->uniform(name + ".ambient",   ambient);
		shader->uniform(name + ".diffuse",   diffuse);
		shader->uniform(name + ".specular",  specular);
	}
};

struct SpotLight : public ILight
{
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;
	float linear;
	float quadratic;
	float constant;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	SpotLight(
		vec3 position = {},
		vec3 direction = {0, -1, 0},
		float cutOff = cos(radians(12.5f)),
		float outerCutOff = cos(radians(15.f)),
		float linear = 0.7f,
		float quadratic = 1.8f,
		float constant = 1,
		vec3 ambient = vec3(0),
		vec3 diffuse = vec3(1),
		vec3 specular = vec3(1)
	) :
		position(position),
		direction(direction),
		cutOff(cutOff),
		outerCutOff(outerCutOff),
		linear(linear),
		quadratic(quadratic),
		constant(constant),
		ambient(ambient),
		diffuse(diffuse),
		specular(specular)
	{
	}

	virtual LightType type() override
	{
		return LightType::SPOT;
	}

	virtual void apply(shared_ptr<Program> shader, string name) override
	{
		shader->uniform(name + ".position",    position);
		shader->uniform(name + ".direction",   direction);
		shader->uniform(name + ".cutOff",      cutOff);
		shader->uniform(name + ".outerCutOff", outerCutOff);
		shader->uniform(name + ".constant",    constant);
		shader->uniform(name + ".linear",      linear);
		shader->uniform(name + ".quadratic",   quadratic);
		shader->uniform(name + ".ambient",     ambient);
		shader->uniform(name + ".diffuse",     diffuse);
		shader->uniform(name + ".specular",    specular);
	}
};
