//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_CHARACTER_H
#define SURVIVE_CHARACTER_H


struct Character
{
    int m_Id;
    int m_X, m_Y;
    int m_Width, m_Height;
    int m_XOffset, m_YOffset;
    int m_Advance;

    Character(int id, int x, int y, int width, int height, int xOffset, int yOffset, int advance);
};


#endif //SURVIVE_CHARACTER_H
