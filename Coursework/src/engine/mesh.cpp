#include "mesh.hpp"

Mesh::Mesh(ProgramPtr shader, const vector<Vertex>& vertices, const vector<uvec3>& indices, const vector<Material>& materials) :
	m_shader(shader),
	m_vertexBuffer(GL_ARRAY_BUFFER),
	m_elementBuffer(GL_ELEMENT_ARRAY_BUFFER),
	m_materials(materials),
	m_drawCount((GLsizei)vertices.size()),
	m_hasIndices(false)
{
	// Bind vertex array
	m_vertexArray.bind();

	// Bind vertex buffer and set vertex buffer data
	m_vertexBuffer.bind();
	m_vertexBuffer.data(vertices, GL_STATIC_DRAW);

	// Set vertex attributes to point to the correct set of vertex data
	m_shader->vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	m_shader->vertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	m_shader->vertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	m_shader->vertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoord));

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

void Mesh::draw(const mat4& model, const mat4& view, const mat4& projection, const vector<ILightPtr>& lights)
{
	// Use the associated shader program
	m_shader->bind();

	// Calculate matrices
	mat4 modelView = view * model;
	mat4 modelViewProjection = projection * modelView;
	mat4 normal = transpose(inverse(modelView));

	// Set model, view and projection uniforms to the associated matrices
	m_shader->uniform("model", model);
	m_shader->uniform("view", view);
	m_shader->uniform("projection", projection);
	m_shader->uniform("modelView", modelView);
	m_shader->uniform("modelViewProjection", modelViewProjection);
	m_shader->uniform("normal", normal);

	// Keep track of number of used texture units
	int textureCount = 0;

	// Use the associated materials
	for (unsigned int i = 0; i < m_materials.size(); i++)
	{
		string name = "material";
		if (i > 0) name += to_string(i);

		if (m_materials[i].diffuse != nullptr)
		{
			glActiveTexture(GL_TEXTURE0 + textureCount);
			m_materials[i].diffuse->bind(GL_TEXTURE_2D);
			m_shader->uniform(name + ".diffuse", textureCount);
			textureCount++;
#ifdef _DEBUG
			glActiveTexture(GL_TEXTURE0);
#endif
		}

		if (m_materials[i].specular != nullptr)
		{
			glActiveTexture(GL_TEXTURE0 + textureCount);
			m_materials[i].diffuse->bind(GL_TEXTURE_2D);
			m_shader->uniform(name + ".specular", textureCount);
			textureCount++;
#ifdef _DEBUG
			glActiveTexture(GL_TEXTURE0);
#endif
		}

		m_shader->uniform(name + ".shininess", m_materials[i].shininess);
	}

	int directionalLights = 0, pointLights = 0, spotLights = 0;
	for (ILightPtr light : lights)
	{
		if (light->type() == LightType::DIRECTIONAL) {
			string name = "directionalLights[" + to_string(directionalLights) + "]";
			light->apply(m_shader, name);
			m_shader->uniform("numDirectionalLights", (int)(directionalLights++));
		}
		else if (light->type() == LightType::POINT) {
			string name = "pointLights[" + to_string(pointLights) + "]";
			light->apply(m_shader, name);
			m_shader->uniform("numPointLights", (int)(pointLights++));
		}
		else if (light->type() == LightType::SPOT) {
			string name = "spotLights[" + to_string(spotLights) + "]";
			light->apply(m_shader, name);
			m_shader->uniform("numSpotLights", (int)(spotLights++));
		}
	}

	// Bind vertex array
	m_vertexArray.bind();

	// Draw elements
	if (m_hasIndices)
		glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, nullptr);
	else
		glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

	// Unbind vertex array
	m_vertexArray.unbind();

	// Unbind the shader
	m_shader->unbind();
}
