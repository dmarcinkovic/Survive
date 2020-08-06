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

    static float minX, maxX;
    static float minY, maxY;
    static float minZ, maxZ;

    static float farHeight, farWidth, nearHeight, nearWidth;

public:
    static void calculateShadowBox(const Camera &camera, const glm::mat4 &lightViewMatrix);

    static std::vector<glm::vec4>
    calcFrustumVertices(const glm::mat4 &rotation, const glm::vec3 &forwardVector, const glm::vec3 &centerNear,
                        const glm::vec3 &centerFar);

private:
    static glm::mat4 calcCameraRotation(const Camera &camera);
};


#endif //SURVIVE_SHADOWBOX_H
