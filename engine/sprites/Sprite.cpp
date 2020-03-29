//
// Created by david on 29. 03. 2020..
//

#include "Sprite.h"

Sprite::Sprite(const Texture &texture, const glm::vec3 &position, float scale, int row, int col)
        : Entity2D(texture, position, scale), m_Row(row), m_Col(col)
{

}

void Sprite::animate(int spritesInSecond, int startRow, int startCol)
{

}

void Sprite::drawSprite(int row, int col)
{
    m_CurrentRow = row;
    m_CurrentCol = col;
}
