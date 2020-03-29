//
// Created by david on 29. 03. 2020..
//

#include "Text.h"

#include <utility>

Text::Text(std::string text, const Texture &texture, const glm::vec3 &position, float scale)
        : Entity2D(texture, position, scale), m_Text(std::move(text))
{

}
