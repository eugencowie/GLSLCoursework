#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm;

class Viewport
{
public:
	Viewport(float aspect = 16 / 9.f, float fov = 45, float near = 0.1f, float far = 1000)
		: m_fov(fov), m_aspect(aspect), m_near(near), m_far(far)
	{
	}

	Viewport(int width, int height, float fov = 45, float near = 0.1f, float far = 1000)
		: Viewport((float)width / height, fov, near, far)
	{
	}

	Viewport(const ivec2& size, float fov = 45, float near = 0.1f, float far = 1000)
		: Viewport(size.x, size.y, fov, near, far)
	{
	}

	mat4 projection() const
	{
		// Create projeciton matrix
		return perspective(radians(m_fov), m_aspect, m_near, m_far);
	}

private:
	float m_fov;
	float m_aspect;
	float m_near;
	float m_far;
};
