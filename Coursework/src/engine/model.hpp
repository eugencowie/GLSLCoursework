#pragma once

#include "mesh.hpp"

#include <tiny_obj_loader.h>
#include <string>
#include <vector>
#include <memory>

using namespace std;
using namespace tinyobj;

class Model
{
public:
	Model(Program& shader, const string& path);

	void draw(const mat4& model = {}, const mat4& view = {}, const mat4& projection = {});

private:
	static vector<Vertex> extractVertices(const attrib_t& attrib, const vector<index_t>& attribIds, vector<size_t>* indices = nullptr);
	static vector<uvec3> transformIndices(vector<size_t> indices);
	static vector<shared_ptr<Texture>> extractTextures(const vector<material_t>& materials, const vector<int>& materialIds, const string& baseDir = "");

	vector<shared_ptr<Mesh>> m_meshes;
};
