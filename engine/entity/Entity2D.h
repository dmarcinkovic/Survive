//
// Created by david on 27. 03. 2020..
//

#ifndef SURVIVE_ENTITY2D_H
#define SURVIVE_ENTITY2D_H

#include "../texture/Texture.h"

#include <glm/vec3.hpp>

struct Entity2D
{
    Texture m_Texture;
    glm::vec3 m_Position;
    float m_ScaleX;
    float m_ScaleY;
    float m_ScaleZ;

    Entity2D(const Texture &texture, const glm::vec3 &position, float scaleX, float scaleY = 1.0f, float scaleZ = 1.0f);

    Entity2D() = default;
};


#endif //SURVIVE_ENTITY2D_H
