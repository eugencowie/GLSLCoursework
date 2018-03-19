#pragma once

#include "util.inl"
#include "shader.inl"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

class Program
{
public:
	Program()
	{
		// Create shader program
		m_program = glCreateProgram();
	}

	~Program()
	{
		// Delete shader program
		glDeleteShader(m_program);
	}

	Program(const string& basePath) : Program()
	{
		// Create vertex and fragment shaders
		Shader vertexShader(GL_VERTEX_SHADER, util::readFile(basePath + ".vert"));
		Shader fragmentShader(GL_FRAGMENT_SHADER, util::readFile(basePath + ".frag"));

		// Attach vertex and fragment shaders
		attach(vertexShader, fragmentShader);

		// Link and validate the shader program
		link();
		validate();

		// Detach vertex and fragment shaders as they are not needed after linking
		detach(vertexShader, fragmentShader);
	}

	void attach(const Shader& shader)
	{
		// Attach shader
		glAttachShader(m_program, shader.handle());
	}

	void detach(const Shader& shader)
	{
		// Detach shader
		glDetachShader(m_program, shader.handle());
	}

	template <typename... Args>
	void attach(const Shader& first, const Args&... args)
	{
		attach(first);
		attach(args...);
	}

	template <typename... Args>
	void detach(const Shader& first, const Args&... args)
	{
		detach(first);
		detach(args...);
	}

	void link()
	{
		// Link shader program
		glLinkProgram(m_program);

		// Check for link errors
		if (!parameter(GL_LINK_STATUS))
			util::panic("Failed to link shader program", infoLog());
	}

	void validate()
	{
		// Validate shader program
		glValidateProgram(m_program);

		// Check for validation errors
		if (!parameter(GL_VALIDATE_STATUS))
			util::panic("Failed to validate shader program", infoLog());
	}

	void bind()
	{
		// Bind shader program
		glUseProgram(m_program);
	}

	void unbind()
	{
#ifdef _DEBUG
		// Unbind shader program
		glUseProgram(0);
#endif
	}

	void uniform(const string& name, int value)
	{
		// Set integer uniform
		glUniform1i(glGetUniformLocation(m_program, name.c_str()), value);
	}

	void uniform(const string& name, vec3 value)
	{
		// Set vec3 uniform
		glUniform3fv(glGetUniformLocation(m_program, name.c_str()), 1, value_ptr(value));
	}

	void uniform(const string& name, mat4 value, bool transpose = false)
	{
		// Set 4x4 matrix uniform
		GLuint location = glGetUniformLocation(m_program, name.c_str());
		glUniformMatrix4fv(location, 1, transpose, value_ptr(value));
	}

	void vertexAttribPointer(const string& name, GLint size, GLenum type, GLboolean normalised, GLsizei stride, const void* pointer)
	{
		// Set vertex attribute pointer and enable vertex attribute array
		GLuint location = glGetAttribLocation(m_program, name.c_str());
		glVertexAttribPointer(location, size, type, normalised, stride, pointer);
		glEnableVertexAttribArray(location);
	}

	GLint parameter(GLenum pname)
	{
		// Get program parameter
		GLint val;
		glGetProgramiv(m_program, pname, &val);
		return val;
	}

	string infoLog()
	{
		// Get program info log
		GLint len = parameter(GL_INFO_LOG_LENGTH);
		string str;
		str.reserve(len);
		glGetProgramInfoLog(m_program, len, nullptr, &str[0]);
		return str;
	}

private:
	GLuint m_program;

	// Rule of five
	Program(Program&&) = delete;
	Program(const Program&) = delete;
	Program& operator=(Program&&) = delete;
	Program& operator=(const Program&) = delete;
};
