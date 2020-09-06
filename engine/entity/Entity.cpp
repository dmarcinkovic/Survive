//
// Created by david on 27. 03. 2020..
//

#include "Entity.h"

Entity::Entity(const TexturedModel &texture, const glm::vec3 &position, float scaleX, float scaleY, float scaleZ)
        : m_Texture(texture), m_Position(position), m_ScaleX(scaleX), m_ScaleY(scaleY), m_ScaleZ(scaleZ)
{

}