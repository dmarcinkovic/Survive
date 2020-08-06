//
// Created by david on 06. 08. 2020..
//

#include <glm/gtc/matrix_transform.hpp>

#include "ShadowBox.h"
#include "../constant/Constants.h"

void ShadowBox::calculateShadowBox(const Camera &camera, const glm::mat4 &lightViewMatrix)
{
    const glm::mat4 rotation = calcCameraRotation(camera);
    const glm::vec3 forwardVector = FORWARD * rotation;

    glm::vec3 toFar = forwardVector * Constants::SHADOW_DISTANCE;
    glm::vec3 toNear = forwardVector * Constants::NEAR;

    glm::vec3 centerNear = toNear + camera.m_Position;
    glm::vec3 centerFar = toFar + camera.m_Position;


}

glm::mat4 ShadowBox::calcCameraRotation(const Camera &camera)
{
    glm::mat4 rotation{};

    const static glm::vec3 up{0, 1, 0};
    const static glm::vec3 right{1, 0, 0};

    rotation = glm::rotate(rotation, glm::radians(-camera.m_Yaw), up);
    rotation = glm::rotate(rotation, -camera.m_Pitch, right);

    return rotation;
}

std::vector<glm::vec4> ShadowBox::calcFrustumVertices(const glm::mat4 &rotation, const glm::vec3 &forwardVector,
                                                      const glm::vec3 &centerNear, const glm::vec3 &centerFar)
{
    glm::vec3 up = UP * rotation;
    glm::vec3 right = glm::cross(forwardVector, up);
    glm::vec3 down = -up;
    glm::vec3 left = -right;

    glm::vec3 farTop = centerFar + up * farHeight;
    glm::vec3 farBottom = centerFar + down * farHeight;
    glm::vec3 nearTop = centerNear + up * nearHeight;
    glm::vec3 nearBottom = centerNear + down * nearHeight;

    std::vector<glm::vec4> points(8);
    

    return points;
}

glm::vec4 ShadowBox::calcLightSpaceFrustumCorner(const glm::mat4 &lightViewMatrix, const glm::vec3 &startPoint,
                                                 const glm::vec3 &direction, float width)
{
    return lightViewMatrix * glm::vec4{startPoint + direction * width, 1};
}
