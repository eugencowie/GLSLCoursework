#include "mesh.hpp"

Mesh::Mesh(Program& shader, const vector<Vertex>& vertices, const vector<uvec3>& indices, const vector<shared_ptr<Texture>>& textures) :
	m_shader(shader),
	m_vertexBuffer(GL_ARRAY_BUFFER),
	m_elementBuffer(GL_ELEMENT_ARRAY_BUFFER),
	m_textures(textures),
	m_drawCount((GLsizei)vertices.size())
{
	// Bind vertex array
	m_vertexArray.bind();

	// Bind vertex buffer and set vertex buffer data
	m_vertexBuffer.bind();
	m_vertexBuffer.data(vertices, GL_STATIC_DRAW);

	// Set vertex attributes to point to the correct set of vertex data
	m_shader.vertexAttribPointer("vertexPosition", 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	m_shader.vertexAttribPointer("vertexNormal", 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	m_shader.vertexAttribPointer("vertexColor", 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	m_shader.vertexAttribPointer("vertexTexCoord", 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoord));

	// Bind element buffer and set element buffer data
	if (indices.size() > 0)
	{
		m_elementBuffer.bind();
		m_elementBuffer.data(indices, GL_STATIC_DRAW);
		m_drawCount = (GLsizei)(indices.size() * 3);
		m_hasIndices = true;
	}

	// Unbind the vertex array
	m_vertexArray.unbind();
}

void Mesh::draw(const mat4& model, const mat4& view, const mat4& projection)
{
	// Use the associated shader program
	m_shader.bind();

	// Use the associated textures
	int textureCount = 0;
	for (unsigned int i = 0; i < m_textures.size(); i++)
	{
		// Activate texture unit
		glActiveTexture(GL_TEXTURE0 + i);

		// Bind the texture to this texture unit
		m_textures[i]->bind(GL_TEXTURE_2D);

		// Set texture uniform to this texture unit
		string name = "texture" + to_string(textureCount++);
		m_shader.uniform(name, i);

#ifdef _DEBUG
		// Unbind texture unit
		glActiveTexture(GL_TEXTURE0);
#endif
	}

	// Set model, view and projection uniforms to the associated matrices
	m_shader.uniform("modelViewProjection", projection * view * model);
	m_shader.uniform("projection", projection);
	m_shader.uniform("view", view);
	m_shader.uniform("model", model);

	// Bind vertex array
	m_vertexArray.bind();

	// Bind buffer (not needed on OpenGL 3+)
	if (m_hasIndices)
		m_elementBuffer.bind();
	else
		m_vertexBuffer.bind();

	// Draw elements
	if (m_hasIndices)
		glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, nullptr);
	else
		glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

	// Unbind vertex array
	m_vertexArray.unbind();

	// Unbind the shader
	m_shader.unbind();
}
