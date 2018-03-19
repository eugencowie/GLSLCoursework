#pragma once

#include <glm/glm.hpp>

using namespace glm;

struct PointLight
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	PointLight(vec3 position = {}, vec3 ambient = vec3(0.25f), vec3 diffuse = vec3(1), vec3 specular = vec3(1))
		: position(position), ambient(ambient), diffuse(diffuse), specular(specular)
	{
	}
};
