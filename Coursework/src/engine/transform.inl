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
		// Create model matrix
		mat4 model = {};

		// Apply translation to model matrix
		model = translate(model, m_position);

		// Apply all rotations to model matrix
		for (Rotation rot : m_rotations)
			model = rotate(model, radians(rot.angle), rot.axis);

		// Apply scaling to model matrix
		model = scale(model, m_scale);

		// Return model matrix
		return model;
	}

	vec3 position() const
	{
		// Return position
		return m_position;
	}

	void position(vec3 newPosition)
	{
		// Set position
		m_position = newPosition;
	}

	void move(vec3 offset)
	{
		// Update position
		m_position += offset;
	}

	void rotations(const vector<Rotation>& rotations)
	{
		// Set list of rotations
		m_rotations = rotations;
	}

private:
	vec3 m_position;
	vector<Rotation> m_rotations;
	vec3 m_scale;
};
