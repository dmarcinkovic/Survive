//
// Created by david on 28. 03. 2020..
//

#include "Maths.h"

glm::mat4 Maths::createTransformationMatrix(const glm::vec3 &translation, float scale,
                                            float rotationX, float rotationY, float rotationZ)
{
    glm::mat4 matrix{1.0f};

    matrix = glm::translate(matrix, translation);

    matrix = glm::rotate(matrix, glm::radians(rotationX), glm::vec3{1, 0, 0});
    matrix = glm::rotate(matrix, glm::radians(rotationY), glm::vec3{0, 1, 0});
    matrix = glm::rotate(matrix, glm::radians(rotationZ), glm::vec3{0, 0, 1});

    matrix = glm::scale(matrix, glm::vec3{scale, scale, scale});

    return matrix;
}