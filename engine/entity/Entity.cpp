//
// Created by david on 27. 03. 2020..
//

#include "Entity.h"

Entity::Entity(const TexturedModel &texture, const glm::vec3 &position, const glm::vec3 &scale)
		: m_Texture(texture), m_Position(position), m_Scale(scale)
{

}
