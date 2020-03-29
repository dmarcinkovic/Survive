//
// Created by david on 29. 03. 2020..
//

#include <cmath>

#include "Sprite.h"
#include "../display/Display.h"

Sprite::Sprite(const Texture &texture, const glm::vec3 &position, float scale, int row, int col)
        : Entity2D(texture, position, scale), m_Row(row), m_Col(col)
{

}

void Sprite::animate(int spritesInSecond, int startRow, int startCol)
{
    animate(spritesInSecond, startRow, startCol, m_Row - 1, m_Col - 1);
}

void Sprite::animate(int spritesInSecond, int startRow, int startCol, int endRow, int endCol)
{
    m_Animate = true;
    m_SpritesInSecond = spritesInSecond;
    m_EndRow = endRow;
    m_EndCol = endCol;
    m_CurrentFrameIndex = startRow * m_Col + startCol;
}

void Sprite::drawSprite(int row, int col)
{
    m_CurrentFrameIndex = row * m_Col + col;
}

void Sprite::animate()
{
    static int startIndex = m_CurrentFrameIndex;
    m_CurrentFrameIndex = startIndex + calculateFrameIndex(startIndex, m_EndRow * m_Col + m_EndCol);
}

int Sprite::calculateFrameIndex(int startIndex, int endIndex)
{
    m_Time += Display::getFrameTime() * m_SpritesInSecond;
    m_Time = std::fmod(m_Time, endIndex - startIndex + 1);

    return std::floor(m_Time);
}
