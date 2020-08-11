//
// Created by david on 06. 08. 2020..
//

#ifndef SURVIVE_SHADOWBOX_H
#define SURVIVE_SHADOWBOX_H

#include <glm/glm.hpp>
#include <vector>
#include "../camera/Camera.h"

class ShadowBox
{
private:
    constexpr static const float OFFSET = 10.0f;
    constexpr static const glm::vec4 UP = glm::vec4{0, 1, 0, 0};
    constexpr static const glm::vec4 FORWARD = glm::vec4{0, 0, -1, 0};

    float minX, maxX;
    float minY, maxY;
    float minZ, maxZ;

    float farHeight, farWidth, nearHeight, nearWidth;

public:
    ShadowBox();

    void calculateShadowBox(const Camera &camera, const glm::mat4 &lightViewMatrix);

private:
    [[nodiscard]] std::vector<glm::vec4>
    calcFrustumVertices(const glm::mat4 &lightViewMatrix, const glm::mat4 &rotation, const glm::vec3 &forwardVector,
                        const glm::vec3 &centerNear, const glm::vec3 &centerFar) const;

    static glm::mat4 calcCameraRotation(const Camera &camera);

    static glm::vec4 calcLightSpaceFrustumCorner(const glm::mat4 &lightViewMatrix, const glm::vec3 &startPoint,
                                                 const glm::vec3 &direction, float width);

    void calculateWidthAndHeight();

    static float aspectRatio();
};


#endif //SURVIVE_SHADOWBOX_H
