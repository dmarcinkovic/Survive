//
// Created by david on 06. 08. 2020..
//

#include <glm/gtc/matrix_transform.hpp>

#include "ShadowBox.h"
#include "../constant/Constants.h"
#include "../display/Display.h"

ShadowBox::ShadowBox()
{
    calculateWidthAndHeight();
}

void ShadowBox::calculateShadowBox(const Camera &camera, const glm::mat4 &lightViewMatrix) const
{
    const glm::mat4 rotation = calcCameraRotation(camera);
    const glm::vec3 forwardVector = FORWARD * rotation;

    glm::vec3 toFar = forwardVector * Constants::SHADOW_DISTANCE;
    glm::vec3 toNear = forwardVector * Constants::NEAR;

    glm::vec3 centerNear = toNear + camera.m_Position;
    glm::vec3 centerFar = toFar + camera.m_Position;

    auto points = calcFrustumVertices(lightViewMatrix, rotation, forwardVector, centerNear, centerFar);

    m_MinX = m_MaxX = points.front().x;
    m_MinY = m_MaxY = points.front().y;
    m_MinZ = m_MaxZ = points.front().z;

    for (int i = 1; i < points.size(); ++i)
    {
        m_MaxX = std::max(points[i].x, m_MaxX);
        m_MaxY = std::max(points[i].y, m_MaxY);
        m_MaxZ = std::max(points[i].z, m_MaxZ);

        m_MinX = std::min(points[i].x, m_MinX);
        m_MinZ = std::min(points[i].y, m_MinY);
        m_MinY = std::min(points[i].z, m_MinZ);
    }

    m_MaxZ += OFFSET;
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
    glm::vec3 left = -right;
    glm::vec3 down = -up;

    glm::vec3 farTop = centerFar + up * m_FarHeight;
    glm::vec3 farBottom = centerFar + down * m_FarHeight;
    glm::vec3 nearTop = centerNear + up * m_NearHeight;
    glm::vec3 nearBottom = centerNear + down * m_NearHeight;

    std::vector<glm::vec4> points(8);
    points[0] = calcLightSpaceFrustumCorner(lightViewMatrix, farTop, right, m_FarWidth);
    points[1] = calcLightSpaceFrustumCorner(lightViewMatrix, farTop, left, m_FarWidth);
    points[2] = calcLightSpaceFrustumCorner(lightViewMatrix, farBottom, right, m_FarWidth);
    points[3] = calcLightSpaceFrustumCorner(lightViewMatrix, farBottom, left, m_FarWidth);
    points[4] = calcLightSpaceFrustumCorner(lightViewMatrix, nearTop, right, m_NearWidth);
    points[5] = calcLightSpaceFrustumCorner(lightViewMatrix, nearTop, left, m_NearWidth);
    points[6] = calcLightSpaceFrustumCorner(lightViewMatrix, nearBottom, right, m_NearWidth);
    points[7] = calcLightSpaceFrustumCorner(lightViewMatrix, nearBottom, left, m_NearWidth);

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

    m_FarWidth = static_cast<float>(Constants::SHADOW_DISTANCE * fieldOfViewTan);
    m_NearWidth = static_cast<float>(Constants::NEAR * fieldOfViewTan);

    const float ratio = aspectRatio();
    m_FarHeight = m_FarWidth / ratio;
    m_NearHeight = m_NearWidth / ratio;
}

float ShadowBox::aspectRatio()
{
    auto[width, height] = Display::getWindowSize();
    return static_cast<float>(width) / height;
}

glm::vec3 ShadowBox::center(const glm::mat4 &lightViewMatrix) const
{
    float x = (m_MinX + m_MaxX) / 2.0f;
    float y = (m_MinY + m_MaxY) / 2.0f;
    float z = (m_MinZ + m_MaxZ) / 2.0f;

    glm::mat4 invertedLight = glm::inverse(lightViewMatrix);

    return glm::vec3{glm::vec4{x, y, z, 1} * invertedLight};
}

float ShadowBox::width() const
{
    return m_MaxX - m_MinX;
}

float ShadowBox::height() const
{
    return m_MaxY - m_MinY;
}

float ShadowBox::length() const
{
    return m_MaxZ - m_MinZ;
}
