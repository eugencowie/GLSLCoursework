#pragma once

#include <glad/glad.h>

class VertexArray
{
public:
	VertexArray()
	{
		// Generate vertex array
		glGenVertexArrays(1, &m_vertexArray);
	}

	~VertexArray()
	{
		// Delete vertex array
		glDeleteVertexArrays(1, &m_vertexArray);
	}

	void bind()
	{
		// Bind vertex array
		glBindVertexArray(m_vertexArray);
	}

	void unbind()
	{
#ifdef _DEBUG
		// Unbind vertex array
		glBindVertexArray(0);
#endif
	}

private:
	GLuint m_vertexArray;

	// Rule of five
	VertexArray(VertexArray&&) = delete;
	VertexArray(const VertexArray&) = delete;
	VertexArray& operator=(VertexArray&&) = delete;
	VertexArray& operator=(const VertexArray&) = delete;
};
