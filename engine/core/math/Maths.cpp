//
// Created by david on 28. 03. 2020..
//

#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Maths.h"
#include "Constants.h"

glm::mat4 Survive::Maths::createTransformationMatrix(const glm::vec3 &translation, const glm::vec3 &scale,
													 const glm::vec3 &rotation)
{
	glm::mat4 matrix{1.0f};

	matrix = glm::translate(matrix, translation);

	matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3{1, 0, 0});
	matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3{0, 1, 0});
	matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3{0, 0, 1});

	matrix = glm::scale(matrix, scale);

	return matrix;
}

glm::mat4 Survive::Maths::createProjectionMatrix(float fieldOfView, float width, float height)
{
	float aspectRatio = width / height;

	return glm::perspective(fieldOfView, aspectRatio, Constants::NEAR, Constants::FAR);
}

glm::mat4 Survive::Maths::createViewMatrix(float pitch, float yaw, const glm::vec3 &position)
{
	glm::mat4 viewMatrix{1.0};
	viewMatrix = glm::rotate(viewMatrix, glm::radians(pitch), glm::vec3{1, 0, 0});
	viewMatrix = glm::rotate(viewMatrix, glm::radians(yaw), glm::vec3{0, 1, 0});

	viewMatrix = glm::translate(viewMatrix, -position);
	return viewMatrix;
}

glm::mat4 Survive::Maths::createLightViewMatrix(const glm::vec3 &lightPosition)
{
	return glm::lookAt(lightPosition, glm::vec3{0.0f}, glm::vec3{0, 1, 0});
}

glm::mat4 Survive::Maths::createLightProjectionMatrix()
{
	return glm::ortho(Constants::LEFT, Constants::RIGHT, Constants::BOTTOM,
					  Constants::TOP, Constants::NEAR, Constants::FAR);
}

glm::mat4 Survive::Maths::createOrthographicProjectionMatrix(float width, float height)
{
	return glm::ortho(-width, width, -height, height);
}

glm::mat4 Survive::Maths::recomposeMatrixFromComponents(const glm::vec3 &translation, const glm::vec3 &scale,
														const glm::vec3 &rotation)
{
	return glm::translate(glm::mat4(1.0f), translation) *
		   glm::toMat4(glm::quat(glm::radians(rotation))) *
		   glm::scale(glm::mat4(1.0f), scale);
}

