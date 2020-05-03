//
// Created by david on 03. 05. 2020..
//

#ifndef SURVIVE_BUTTON_H
#define SURVIVE_BUTTON_H

#include <glm/glm.hpp>

#include "../../entity/Entity2D.h"

struct Button : public Entity2D
{
    glm::vec4 m_Color;

    explicit Button(const Texture &texture, const glm::vec3 &position, float scaleX, float scaleY,
                    const glm::vec4 &color);
};


#endif //SURVIVE_BUTTON_H
