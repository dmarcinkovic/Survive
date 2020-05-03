//
// Created by david on 03. 05. 2020..
//

#include "Button.h"

Button::Button(const Texture &texture, const glm::vec3 &position, float scaleX, float scaleY, const glm::vec4 &color)
        : Entity2D(texture, position, scaleX, scaleY), m_Color(color)
{

}
