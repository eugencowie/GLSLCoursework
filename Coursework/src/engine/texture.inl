#pragma once

#include "util.inl"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <stb_image.h>

#include <string>
#include <memory>

using namespace std;
using namespace glm;

class Texture
{
public:
	Texture()
	{
		// Generate texture
		glGenTextures(1, &m_texture);
	}

	~Texture()
	{
		// Delete texture
		glDeleteTextures(1, &m_texture);
	}

	Texture(const string& path, bool flipUVs = true) : Texture()
	{
		// Load texture from file
		load(path, flipUVs);
	}

	void bind(GLenum target)
	{
		// Bind texture to target
		glBindTexture(target, m_texture);
	}

	void unbind(GLenum target)
	{
#ifdef _DEBUG
		// Unbind texture from target
		glBindTexture(target, 0);
#endif
	}

	void load(const string& path, bool flipUVs = false)
	{
		// Set image file path
		this->m_path = path;

		// Flip image vertically (if specified)
		stbi_set_flip_vertically_on_load(flipUVs);

		// Load image data from file
		unsigned char* data = stbi_load(path.c_str(), &m_size.x, &m_size.y, nullptr, STBI_rgb_alpha);
		if (!data) util::panic("Failed to load texture image", path);

		// Set image data
		texture(GL_TEXTURE_2D, data);

		// Free image data as it is no longer needed
		stbi_image_free(data);
	}

	void texture(GLenum target, unsigned char* data)
	{
		// Bind texture to target
		bind(target);

		// Set texture parameters
		glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Set image data
		glTexImage2D(target, 0, GL_RGBA, m_size.x, m_size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		// Unbind texture from target
		unbind(target);
	}

private:
	GLuint m_texture;
	ivec2 m_size;
	string m_path;

	// Rule of five
	Texture(Texture&&) = delete;
	Texture(const Texture&) = delete;
	Texture& operator=(Texture&&) = delete;
	Texture& operator=(const Texture&) = delete;
};
