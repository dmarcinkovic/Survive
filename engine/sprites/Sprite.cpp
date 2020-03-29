//
// Created by david on 29. 03. 2020..
//

#include "Sprite.h"

Sprite::Sprite(const Texture &texture, const glm::vec3 &position, float scale, int row, int col)
        : Entity2D(texture, position, scale), row(row), col(col)
{

}
