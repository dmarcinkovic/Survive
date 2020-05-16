//
// Created by david on 28. 03. 2020..
//

#include "Maths.h"
#include "../display/Display.h"

glm::mat4 Maths::createTransformationMatrix(const glm::vec3 &translation, float scaleX, float scaleY, float scaleZ,
                                            float rotationX, float rotationY, float rotationZ)
{
    glm::mat4 matrix{1.0f};

    matrix = glm::translate(matrix, translation);

    matrix = glm::rotate(matrix, glm::radians(rotationX), glm::vec3{1, 0, 0});
    matrix = glm::rotate(matrix, glm::radians(rotationY), glm::vec3{0, 1, 0});
    matrix = glm::rotate(matrix, glm::radians(rotationZ), glm::vec3{0, 0, 1});

    matrix = glm::scale(matrix, glm::vec3{scaleX, scaleY, scaleZ});

    return matrix;
}

glm::mat4 Maths::createProjectionMatrix(float fieldOfView, float near, float far)
{
    auto[width, height] = Display::getWindowSize();
    float aspectRatio = static_cast<float>(width) / static_cast<float >(height);

    return glm::perspective(fieldOfView, aspectRatio, near, far);
}

glm::mat4 Maths::createViewMatrix(const Camera &camera)
{
    glm::mat4 viewMatrix{1.0};
    viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.m_Pitch), glm::vec3{1, 0, 0});
    viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.m_Yaw), glm::vec3{0, 1, 0});

    viewMatrix = glm::translate(viewMatrix, -camera.m_Position);
    return viewMatrix;
}
