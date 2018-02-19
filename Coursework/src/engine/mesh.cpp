#include "mesh.hpp"

Mesh::Mesh(Program& shader, const vector<Vertex>& vertices, const vector<uvec3>& indices) :
	m_shader(shader),
	m_vertexBuffer(GL_ARRAY_BUFFER),
	m_elementBuffer(GL_ELEMENT_ARRAY_BUFFER),
	m_drawCount(GLsizei(indices.size() * 3))
{
	// Bind vertex array
	m_vertexArray.bind();

	// Bind vertex buffer and set vertex buffer data
	m_vertexBuffer.bind();
	m_vertexBuffer.data(vertices, GL_STATIC_DRAW);

	// Set vertex attributes to point to the correct set of vertex data
	m_shader.vertexAttribPointer("vertexPosition", 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	m_shader.vertexAttribPointer("vertexColor", 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));

	// Bind element buffer and set element buffer data
	m_elementBuffer.bind();
	m_elementBuffer.data(indices, GL_STATIC_DRAW);

	// Unbind the vertex array
	m_vertexArray.unbind();
}

void Mesh::draw(const mat4& model, const mat4& view, const mat4& projection)
{
	// Use the associated shader program
	m_shader.bind();

	// Set model, view and projection uniforms to the associated matrices
	m_shader.uniform("modelViewProjection", projection * view * model);
	m_shader.uniform("projection", projection);
	m_shader.uniform("view", view);
	m_shader.uniform("model", model);

	// Bind vertex array
	m_vertexArray.bind();

	// Bind element buffer (not needed on OpenGL 3+)
	m_elementBuffer.bind();

	// Draw elements
	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, nullptr);

	// Unbind vertex array
	m_vertexArray.unbind();

	// Unbind the shader
	m_shader.unbind();
}
