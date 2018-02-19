#pragma once

#include "program.inl"
#include "vertex.inl"
#include "vertex_array.inl"
#include "buffer.inl"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

using namespace std;
using namespace glm;

class Mesh
{
public:
	Mesh(Program& shader, const vector<Vertex>& vertices, const vector<uvec3>& indices);
	void draw(const mat4& model = {}, const mat4& view = {}, const mat4& projection = {});

private:
	Program& m_shader;
	VertexArray m_vertexArray;
	Buffer m_vertexBuffer;
	Buffer m_elementBuffer;
	GLsizei m_drawCount;

	// Rule of five
	Mesh(Mesh&&) = delete;
	Mesh(const Mesh&) = delete;
	Mesh& operator=(Mesh&&) = delete;
	Mesh& operator=(const Mesh&) = delete;
};
