#pragma once

#include "mesh.hpp"

#include <string>
#include <vector>
#include <memory>

using namespace std;

class Model
{
public:
	Model(Program& shader, const string& path);

	void draw(const mat4& model = {}, const mat4& view = {}, const mat4& projection = {});

private:
	vector<shared_ptr<Mesh>> m_meshes;
};
