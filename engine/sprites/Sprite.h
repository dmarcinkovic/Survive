//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_SPRITE_H
#define SURVIVE_SPRITE_H

#include "../entity/Entity2D.h"

class Sprite : public Entity2D
{
private:
    double m_Time{};
    int m_EndRow{}, m_EndCol{};

public:
    int m_CurrentFrameIndex{};
    const int m_Row, m_Col;
    bool m_Animate{};

    int m_SpritesInSecond{};

    Sprite(const Texture &texture, const glm::vec3 &position, float scale, int row = 1, int col = 1);

    void animate(int spritesInSecond, int startRow = 0, int startCol = 0);

    void animate(int spritesInSecond, int startRow, int startCol, int endRow, int endCol);

    void drawSprite(int row, int col);

    void animate();

private:
    int calculateFrameIndex(int startIndex, int endIndex);
};


#endif //SURVIVE_SPRITE_H
