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
    m_Animate = true;
    m_CurrentRow = startRow;
    m_CurrentCol = startCol;
    m_SpritesInSecond = spritesInSecond;
}

void Sprite::drawSprite(int row, int col)
{
    m_CurrentRow = row;
    m_CurrentCol = col;
}

void Sprite::animate()
{
    m_Time += Display::getFrameTime();
    m_Time = std::fmod(m_Time, 1.0);

    int frameIndex = std::floor(m_Time * m_SpritesInSecond);

    if (m_LastFrameIndex != frameIndex)
    {
        ++m_CurrentFrameIndex;
        m_CurrentFrameIndex %= m_Row * m_Col;
    }

    m_CurrentCol = m_CurrentFrameIndex % m_Col;
    m_CurrentRow = std::floor(m_CurrentFrameIndex / m_Col);

    m_LastFrameIndex = frameIndex;
}
