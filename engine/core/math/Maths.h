//
// Created by david on 28. 03. 2020..
//

#ifndef SURVIVE_MATHS_H
#define SURVIVE_MATHS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Survive
{
	class Maths
	{
	public:
		static glm::mat4
		createTransformationMatrix(const glm::vec3 &translation, const glm::vec3 &scale = glm::vec3{1.0f},
								   const glm::vec3 &rotation = glm::vec3{});

		static glm::mat4 createProjectionMatrix(float fieldOfView, float near, float far, float width, float height);

		static glm::mat4 createViewMatrix(float pitch, float yaw, const glm::vec3 &position);

		static glm::mat4 createLightViewMatrix(const glm::vec3 &lightPosition);

		static glm::mat4 createLightProjectionMatrix(float near, float far);

		static glm::mat4 createOrthographicProjectionMatrix(float width, float height);

		static glm::mat4
		recomposeMatrixFromComponents(const glm::vec3 &translation, const glm::vec3 &scale, const glm::vec3 &rotation);
	};
}

#endif //SURVIVE_MATHS_H
