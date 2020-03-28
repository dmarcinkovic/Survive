//
// Created by david on 28. 03. 2020..
//

#ifndef SURVIVE_MATHS_H
#define SURVIVE_MATHS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Maths
{
public:
    static glm::mat4 createTransformationMatrix(const glm::vec3 &translation, float scale = 1.0f,
                                                float rotationX = 0.0f, float rotationY = 0.0f, float rotationZ = 0.0f);
};

#endif //SURVIVE_MATHS_H
