//
// Created by david on 28. 03. 2020..
//

#ifndef SURVIVE_MATHS_H
#define SURVIVE_MATHS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../camera/Camera.h"

class Maths
{
public:
    static glm::mat4 createTransformationMatrix(const glm::vec3 &translation, float scaleX = 1.0f,
                                                float scaleY = 1.0f, float scaleZ = 1.0f,
                                                float rotationX = 0.0f, float rotationY = 0.0f, float rotationZ = 0.0f);

    static glm::mat4 createProjectionMatrix(float fieldOfView, float near, float far);

    static glm::mat4 createViewMatrix(const Camera &camera);
};

#endif //SURVIVE_MATHS_H
