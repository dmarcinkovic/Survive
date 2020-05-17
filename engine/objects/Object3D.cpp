//
// Created by david on 17. 05. 2020..
//

#include "Object3D.h"

Object3D::Object3D(const Texture &texture, const glm::vec3 &position, const glm::vec3 &rotation, float scaleX,
                   float scaleY, float scaleZ)
        : Entity(texture, position, scaleX, scaleY, scaleZ), m_Rotation(rotation)
{

}