#pragma once

#include <glm/glm.hpp>

using namespace glm;

struct DirectionalLight
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;
	float linear;
	float quadratic;
	float constant;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	PointLight(vec3 position = {}, float linear = 0.7f, float quadratic = 1.8f, float constant = 1, vec3 ambient = vec3(1), vec3 diffuse = vec3(1), vec3 specular = vec3(1))
		: position(position), linear(linear), quadratic(quadratic), constant(constant), ambient(ambient), diffuse(diffuse), specular(specular)
	{
	}
};

struct SpotLight
{
	vec3 position;
	vec3 direction;
	float constant;
	float linear;
	float quadratic;
	float cutOff;
	float outerCutOff;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
