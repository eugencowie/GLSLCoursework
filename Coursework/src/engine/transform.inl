#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>

using namespace std;
using namespace glm;

struct Rotation
{
	float angle = 0;
	vec3 axis = {0,1,0};
};

class Transform
{
public:
	Transform(vec3 position = {}, vec3 scale = {1,1,1}, const vector<Rotation>& rotations = {})
		: m_position(position), m_scale(scale), m_rotations(rotations)
	{
	}

	mat4 model() const
	{
		mat4 model = {};

		model = translate(model, m_position);

		for (Rotation rot : m_rotations)
			model = rotate(model, radians(rot.angle), rot.axis);

		model = scale(model, m_scale);

		return model;
	}

	vec3 position() const
	{
		return m_position;
	}

	void move(vec3 offset)
	{
		m_position += offset;
	}

private:
	vec3 m_position;
	vec3 m_scale;

	vector<Rotation> m_rotations;
};
