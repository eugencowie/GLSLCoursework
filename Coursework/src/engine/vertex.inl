#pragma once

#include <glm/glm.hpp>

using namespace glm;

struct Vertex
{
	vec3 position;
	vec3 normal;
	vec4 color;
	vec2 texCoord;
};
