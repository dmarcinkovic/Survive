//
// Created by david on 17. 05. 2020..
//

#ifndef SURVIVE_CAMERA_H
#define SURVIVE_CAMERA_H

#include <glm/glm.hpp>

struct Camera
{
	glm::vec3 position{};
	float pitch{};
	float yaw{};

	glm::vec3 rotation{};
};


#endif //SURVIVE_CAMERA_H
