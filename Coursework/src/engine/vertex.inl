#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>

using namespace glm;

struct Vertex
{
	vec3 position;
	vec3 normal;
	vec4 color;
	vec2 texCoord;

	bool operator==(const Vertex& other) const
	{
		return position == other.position
			&& normal == other.normal
			&& color == other.color
			&& texCoord == other.texCoord;
	}
};

// https://stackoverflow.com/a/2595226
namespace boost
{
	template <class T>
	inline void hash_combine(std::size_t& seed, const T& v)
	{
		std::hash<T> hasher;
		seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
}

// https://vulkan-tutorial.com/Loading_models
namespace std
{
	template<> struct hash<Vertex>
	{
		size_t operator()(Vertex const& vertex) const
		{
			size_t hash;
			boost::hash_combine(hash, vertex.position);
			boost::hash_combine(hash, vertex.normal);
			boost::hash_combine(hash, vertex.color);
			boost::hash_combine(hash, vertex.texCoord);
			return hash;
		}
	};
}
