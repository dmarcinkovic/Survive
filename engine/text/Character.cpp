//
// Created by david on 29. 03. 2020..
//

#include "Character.h"

Character::Character(int id, float x, float y, float width, float height, float xOffset, float yOffset, float advance,
                     float scaleW, float scaleH)
        : m_Id(id), m_X(x), m_Y(y), m_Width(width), m_Height(height), m_XOffset(xOffset), m_YOffset(yOffset),
          m_Advance(advance), m_ScaleW(scaleW), m_ScaleH(scaleH)
{
    calculateTextureCoordinates(scaleW, scaleH);
}

void Character::calculateTextureCoordinates(float scaleW, float scaleH)
{
    float minX = m_X / scaleW;
    float maxX = (m_X + m_Width) / scaleW;
    float minY = (scaleH - m_Height - m_Y) / scaleH;
    float maxY = (scaleH - m_Y) / scaleH;

    m_TextureCoords.emplace_back(minX);
    m_TextureCoords.emplace_back(maxY);
    m_TextureCoords.emplace_back(minX);
    m_TextureCoords.emplace_back(minY);
    m_TextureCoords.emplace_back(maxX);
    m_TextureCoords.emplace_back(minY);
    m_TextureCoords.emplace_back(maxX);
    m_TextureCoords.emplace_back(minY);
    m_TextureCoords.emplace_back(maxX);
    m_TextureCoords.emplace_back(maxY);
    m_TextureCoords.emplace_back(minX);
    m_TextureCoords.emplace_back(maxY);
}
