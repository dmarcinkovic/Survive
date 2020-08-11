//
// Created by david on 06. 08. 2020..
//

#include <glm/gtc/matrix_transform.hpp>

#include "ShadowBox.h"
#include "../constant/Constants.h"
#include "../display/Display.h"

ShadowBox::ShadowBox()
{

}

void ShadowBox::calculateShadowBox(const Camera &camera, const glm::mat4 &lightViewMatrix)
{
    const glm::mat4 rotation = calcCameraRotation(camera);
    const glm::vec3 forwardVector = FORWARD * rotation;

    glm::vec3 toFar = forwardVector * Constants::SHADOW_DISTANCE;
    glm::vec3 toNear = forwardVector * Constants::NEAR;

    glm::vec3 centerNear = toNear + camera.m_Position;
    glm::vec3 centerFar = toFar + camera.m_Position;

    auto points = calcFrustumVertices(lightViewMatrix, rotation, forwardVector, centerNear, centerFar);

    minX = maxX = points.front().x;
    minY = maxY = points.front().y;
    minZ = maxZ = points.front().z;

    for (int i = 1; i < points.size(); ++i)
    {
        maxX = std::max(points[i].x, maxX);
        maxY = std::max(points[i].y, maxY);
        maxZ = std::max(points[i].z, maxZ);

        minX = std::min(points[i].x, minX);
        minZ = std::min(points[i].y, minY);
        minY = std::min(points[i].z, minZ);
    }

    maxZ += OFFSET;
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

std::vector<glm::vec4>
ShadowBox::calcFrustumVertices(const glm::mat4 &lightViewMatrix, const glm::mat4 &rotation,
                               const glm::vec3 &forwardVector, const glm::vec3 &centerNear,
                               const glm::vec3 &centerFar) const
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
    points[0] = calcLightSpaceFrustumCorner(lightViewMatrix, farTop, right, farWidth);
    points[1] = calcLightSpaceFrustumCorner(lightViewMatrix, farTop, left, farWidth);
    points[2] = calcLightSpaceFrustumCorner(lightViewMatrix, farBottom, right, farWidth);
    points[3] = calcLightSpaceFrustumCorner(lightViewMatrix, farBottom, left, farWidth);
    points[4] = calcLightSpaceFrustumCorner(lightViewMatrix, nearTop, right, nearWidth);
    points[5] = calcLightSpaceFrustumCorner(lightViewMatrix, nearTop, left, nearWidth);
    points[6] = calcLightSpaceFrustumCorner(lightViewMatrix, nearBottom, right, nearWidth);
    points[7] = calcLightSpaceFrustumCorner(lightViewMatrix, nearBottom, left, nearWidth);

    return points;
}

glm::vec4 ShadowBox::calcLightSpaceFrustumCorner(const glm::mat4 &lightViewMatrix, const glm::vec3 &startPoint,
                                                 const glm::vec3 &direction, float width)
{
    return lightViewMatrix * glm::vec4{startPoint + direction * width, 1};
}

void ShadowBox::calculateWidthAndHeight()
{
    double fieldOfViewTan = std::tan(glm::radians(Constants::FIELD_OF_VIEW));

    farWidth = static_cast<float>(Constants::SHADOW_DISTANCE * fieldOfViewTan);
    nearWidth = static_cast<float>(Constants::NEAR * fieldOfViewTan);

    const float ratio = aspectRatio();
    farHeight = farWidth / ratio;
    nearHeight = nearWidth / ratio;
}

float ShadowBox::aspectRatio()
{
    auto[width, height] = Display::getWindowSize();
    return static_cast<float>(width) / height;
}
