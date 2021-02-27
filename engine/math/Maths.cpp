//
// Created by david on 28. 03. 2020..
//

#include <random>
#include "Maths.h"
#include "../display/Display.h"
#include "../constant/Constants.h"

glm::mat4 Maths::projectionMatrix;
glm::mat4 Maths::lightProjectionMatrix;
glm::mat4 Maths::orthographicProjectionMatrix;

glm::mat4 Maths::createTransformationMatrix(const glm::vec3 &translation, const glm::vec3 &scale,
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

glm::mat4 Maths::createProjectionMatrix(float fieldOfView)
{
	auto[width, height] = Display::getWindowSize<float>();
	float aspectRatio = width / height;

	return glm::perspective(fieldOfView, aspectRatio, Constants::NEAR, Constants::FAR);
}

glm::mat4 Maths::createViewMatrix(const Camera &camera)
{
	glm::mat4 viewMatrix{1.0};
	viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.pitch), glm::vec3{1, 0, 0});
	viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.yaw), glm::vec3{0, 1, 0});

	viewMatrix = glm::translate(viewMatrix, -camera.position);
	return viewMatrix;
}

glm::mat4 Maths::createLightViewMatrix(const Light &light)
{
	return glm::lookAt(light.position(), glm::vec3{0.0f}, glm::vec3{0, 1, 0});
}

glm::mat4 Maths::createLightProjectionMatrix()
{
	return glm::ortho(Constants::LEFT, Constants::RIGHT, Constants::BOTTOM,
					  Constants::TOP, Constants::NEAR, Constants::FAR);
}

glm::mat4 Maths::createOrthographicProjectionMatrix(float width, float height)
{
	return glm::ortho(-width, width, -height, height);
}

float Maths::getRandom(float first, float second)
{
	static std::random_device device;
	static std::mt19937_64 mt(device());
	static std::uniform_real_distribution<> distribution(first, second);

	return distribution(mt);
}
