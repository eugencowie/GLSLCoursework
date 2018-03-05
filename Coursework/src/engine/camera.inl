#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class Camera
{
public:
	Camera(const vec3& position, const vec3& target = {0,0,0}, const vec3& up = {0,1,0})
		: m_position(position), m_target(target), m_up(up)
	{
	}

	mat4 view() const
	{
		// Create view matrix
		return lookAt(m_position, m_target, m_up);
	}

private:
	vec3 m_position;
	vec3 m_target;
	vec3 m_up;
};
