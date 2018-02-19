#pragma once

#include "util.inl"
#include <glad/glad.h>
#include <string>

using namespace std;

class Shader
{
public:
	Shader(GLenum type)
	{
		// Create shader
		m_shader = glCreateShader(type);
	}

	~Shader()
	{
		// Delete shader
		glDeleteShader(m_shader);
	}

	Shader(GLenum type, const string& source) : Shader(type)
	{
		// Set shader source
		this->source(source);

		// Compile shader
		compile();
	}

	void source(const string& source)
	{
		// Check source is not empty
		if (source.empty())
			util::panic("Unable to set shader source", "Empty string provided");

		// Set shader source
		const GLchar* data = source.c_str();
		glShaderSource(m_shader, 1, &data, nullptr);
	}

	void compile()
	{
		// Compile shader
		glCompileShader(m_shader);

		// Check for shader compilation errors
		if (!parameter(GL_COMPILE_STATUS))
			util::panic("Failed to compile shader", infoLog());
	}

	GLint parameter(GLenum pname)
	{
		// Get shader parameter
		GLint val;
		glGetShaderiv(m_shader, pname, &val);
		return val;
	}

	string infoLog()
	{
		// Get shader info log
		GLint len = parameter(GL_INFO_LOG_LENGTH);
		string str;
		str.reserve(len);
		glGetShaderInfoLog(m_shader, len, nullptr, &str[0]);
		return str;
	}

	GLuint handle() const
	{
		// Get shader handle
		return m_shader;
	}

private:
	GLuint m_shader;

	// Rule of five
	Shader(Shader&&) = delete;
	Shader(const Shader&) = delete;
	Shader& operator=(Shader&&) = delete;
	Shader& operator=(const Shader&) = delete;
};
