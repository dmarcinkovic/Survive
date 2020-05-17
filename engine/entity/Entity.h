//
// Created by david on 27. 03. 2020..
//

#ifndef SURVIVE_ENTITY_H
#define SURVIVE_ENTITY_H

#include "../texture/Texture.h"

#include <glm/vec3.hpp>

struct Entity
{
    Texture m_Texture;
    glm::vec3 m_Position;
    float m_ScaleX;
    float m_ScaleY;
    float m_ScaleZ;

    Entity(const Texture &texture, const glm::vec3 &position, float scaleX = 1.0f, float scaleY = 1.0f, float scaleZ = 1.0f);

    Entity() = default;
};


#endif //SURVIVE_ENTITY_H
