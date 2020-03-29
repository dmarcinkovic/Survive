//
// Created by david on 29. 03. 2020..
//

#include "Character.h"

Character::Character(int id, float x, float y, float width, float height, float xOffset, float yOffset, float advance, float scaleW,
                     float scaleH)
        : m_Id(id), m_X(x), m_Y(y), m_Width(width), m_Height(height), m_XOffset(xOffset), m_YOffset(yOffset),
          m_Advance(advance)
{
    calculateTextureCoordinates(scaleW, scaleH);
}

void Character::calculateTextureCoordinates(float scaleW, float scaleH)
{
    
}
