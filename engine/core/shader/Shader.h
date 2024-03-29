//
// Created by david on 24. 03. 2020..
//

#ifndef SURVIVE_SHADER_H
#define SURVIVE_SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace Survive
{
	class Shader
	{
	protected:
		GLuint m_VertexShader;
		GLuint m_FragmentShader;
		GLuint m_Program;

	private:
		static GLuint loadShader(const char *source, GLenum type);

		static void debug(GLuint shaderId);

	public:
		Shader(const char *vertexSource, const char *fragmentSource);

		virtual ~Shader();

		void start() const;

		static void stop();

	protected:
		static void loadMatrix(GLint location, const glm::mat4 &matrix);

		static void loadVector3(GLint location, const glm::vec3 &vector);

		static void loadFloat(GLint location, float value);

		static void loadVector4(GLint location, const glm::vec4 &vector);

		static void loadInteger(GLint location, int value);

		static void loadUnsigned(GLint location, unsigned value);
	};
}

#endif //SURVIVE_SHADER_H
