#pragma once

#include "program.inl"
#include "vertex.inl"
#include "texture.inl"
#include "vertex_array.inl"
#include "buffer.inl"
#include "light.inl"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <memory>

using namespace std;
using namespace glm;

struct Material
{
	shared_ptr<Texture> diffuse;
	shared_ptr<Texture> specular;
	float shininess;
};

class Mesh
{
public:
	Mesh(ProgramPtr shader, const vector<Vertex>& vertices, const vector<uvec3>& indices = {}, const vector<Material>& materials = {});
	void draw(const mat4& model = {}, const mat4& view = {}, const mat4& projection = {}, const vector<ILightPtr>& lights = {});

	void shader(ProgramPtr shader)
	{
		// Set mesh shader
		m_shader = shader;
	}

private:
	ProgramPtr m_shader;
	VertexArray m_vertexArray;
	Buffer m_vertexBuffer;
	Buffer m_elementBuffer;
	vector<Material> m_materials;
	GLsizei m_drawCount;
	bool m_hasIndices;

	// Rule of five
	Mesh(Mesh&&) = delete;
	Mesh(const Mesh&) = delete;
	Mesh& operator=(Mesh&&) = delete;
	Mesh& operator=(const Mesh&) = delete;
};
