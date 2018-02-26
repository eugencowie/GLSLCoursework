#include "model.hpp"
#include "util.inl"

#include <tiny_obj_loader.h>
#include <unordered_map>

using namespace tinyobj;

Model::Model(Program& shader, const string& path)
{
	attrib_t attrib;
	vector<shape_t> shapes;
	vector<material_t> materials;
	string err;

	bool obj = LoadObj(&attrib, &shapes, &materials, &err, path.c_str());
	if (!obj) util::panic("Failed to load model: " + path, err);

	for (const shape_t& shape : shapes)
	{
		vector<Vertex> vertices;
		unordered_map<Vertex, size_t> uniqueVertices;
		vector<size_t> allIndices;

		for (const index_t& index : shape.mesh.indices)
		{
			Vertex vertex;

			vertex.position = {
				attrib.vertices[3 * index.vertex_index + 0],
				attrib.vertices[3 * index.vertex_index + 1],
				attrib.vertices[3 * index.vertex_index + 2]
			};

			if (index.normal_index >= 0)
			{
				vertex.normal = {
					attrib.normals[3 * index.normal_index + 0],
					attrib.normals[3 * index.normal_index + 1],
					attrib.normals[3 * index.normal_index + 2]
				};
			}

			vertex.color = vec4(1);

			if (index.texcoord_index >= 0)
			{
				vertex.texCoord = {
					attrib.texcoords[2 * index.texcoord_index + 0],
					attrib.texcoords[2 * index.texcoord_index + 1]
				};
			}

			if (uniqueVertices.count(vertex) == 0)
			{
				uniqueVertices[vertex] = vertices.size();
				vertices.push_back(vertex);
			}

			allIndices.push_back(uniqueVertices[vertex]);
		}

		vector<uvec3> indices;

		for (int i = 2; i < allIndices.size(); i += 3)
		{
			uvec3 index = {
				allIndices[i-2],
				allIndices[i-1],
				allIndices[i]
			};

			indices.push_back(index);
		}

		m_meshes.push_back(make_shared<Mesh>(shader, vertices, indices));
	}
}

void Model::draw(const mat4& model, const mat4& view, const mat4& projection)
{
	for (shared_ptr<Mesh>& mesh : m_meshes)
	{
		mesh->draw();
	}
}
