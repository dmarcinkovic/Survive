//
// Created by david on 17. 05. 2020..
//

#ifndef SURVIVE_CAMERA_H
#define SURVIVE_CAMERA_H

#include <glm/glm.hpp>

struct Camera
{
    glm::vec3 m_Position{};
    float m_Pitch{};
    float  m_Yaw{};

    glm::vec3 m_Rotation{};

    Camera();



};


#endif //SURVIVE_CAMERA_H
