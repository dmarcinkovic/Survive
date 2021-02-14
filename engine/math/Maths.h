//
// Created by david on 28. 03. 2020..
//

#ifndef SURVIVE_MATHS_H
#define SURVIVE_MATHS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../camera/Camera.h"
#include "../light/Light.h"

class Maths
{
public:
	static glm::mat4 projectionMatrix;
	static glm::mat4 lightProjectionMatrix;
	static glm::mat4 orthographicProjectionMatrix;

	static glm::mat4
	createTransformationMatrix(const glm::vec3 &translation, const glm::vec3 &scale = glm::vec3{1.0f, 1.0f, 1.0f},
							   const glm::vec3 &rotation = glm::vec3{});

	static glm::mat4 createProjectionMatrix(float fieldOfView);

	static glm::mat4 createViewMatrix(const Camera &camera);

	static glm::mat4 createLightViewMatrix(const Light &light);

	static glm::mat4 createLightProjectionMatrix();

	static glm::mat4 createOrthographicProjectionMatrix(float width, float height);

	static float getRandom(float first = 0.0f, float second = 1.0f);
};

#endif //SURVIVE_MATHS_H
