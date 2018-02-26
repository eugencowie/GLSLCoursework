#pragma once

#include <glad/glad.h>
#include <vector>

using namespace std;

class Buffer
{
public:
	Buffer(GLenum target) : m_target(target)
	{
		// Generate buffer
		glGenBuffers(1, &m_buffer);
	}

	~Buffer()
	{
		// Delete buffer
		glDeleteBuffers(1, &m_buffer);
	}

	void bind()
	{
		// Bind buffer to target
		glBindBuffer(m_target, m_buffer);
	}

	void unbind()
	{
#ifdef _DEBUG
		// Unbind buffer from target
		glBindBuffer(m_target, 0);
#endif
	}

	template<typename T>
	void data(const vector<T>& data, GLenum usage)
	{
		// Set buffer data
		glBufferData(m_target, data.size() * sizeof(T), &data[0], usage);
	}

private:
	GLenum m_target;
	GLuint m_buffer;

	// Rule of five
	Buffer(Buffer&&) = delete;
	Buffer(const Buffer&) = delete;
	Buffer& operator=(Buffer&&) = delete;
	Buffer& operator=(const Buffer&) = delete;
};
