//
// Created by david on 24. 03. 2020..
//

#include <iostream>

#include "Shader.h"

Survive::Shader::Shader(const char *vertexSource, const char *fragmentSource)
{
	m_VertexShader = loadShader(vertexSource, GL_VERTEX_SHADER);
	m_FragmentShader = loadShader(fragmentSource, GL_FRAGMENT_SHADER);

	m_Program = glCreateProgram();
	glAttachShader(m_Program, m_VertexShader);
	glAttachShader(m_Program, m_FragmentShader);

	glLinkProgram(m_Program);
	glValidateProgram(m_Program);
}

Survive::Shader::~Shader()
{
	glDetachShader(m_Program, m_VertexShader);
	glDetachShader(m_Program, m_FragmentShader);

	glDeleteShader(m_VertexShader);
	glDeleteShader(m_FragmentShader);
	glDeleteProgram(m_Program);
}

void Survive::Shader::start() const
{
	glUseProgram(m_Program);
}

void Survive::Shader::stop()
{
	glUseProgram(0);
}

GLuint Survive::Shader::loadShader(const char *source, GLenum type)
{
	GLuint shader = glCreateShader(type);

	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	debug(shader);

	return shader;
}

void Survive::Shader::debug(GLuint shaderId)
{
	int result;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
		char *message = (char *) alloca(length * sizeof(char));

		glGetShaderInfoLog(shaderId, length, &length, message);

		std::cout << "Error while compiling shader: " << message << "\n";
		glDeleteShader(shaderId);
	}
}

void Survive::Shader::loadMatrix(GLint location, const glm::mat4 &matrix)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void Survive::Shader::loadVector3(GLint location, const glm::vec3 &vector)
{
	glUniform3f(location, vector.x, vector.y, vector.z);
}

void Survive::Shader::loadFloat(GLint location, float value)
{
	glUniform1f(location, value);
}

void Survive::Shader::loadVector4(GLint location, const glm::vec4 &vector)
{
	glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
}

void Survive::Shader::loadInteger(GLint location, int value)
{
	glUniform1i(location, value);
}

void Survive::Shader::loadUnsigned(GLint location, unsigned int value)
{
	glUniform1ui(location, value);
}
