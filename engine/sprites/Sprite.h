//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_SPRITE_H
#define SURVIVE_SPRITE_H


#include "../entity/Entity2D.h"

struct Sprite : public Entity2D
{
    int m_Row;
    int m_Col;
    int m_CurrentRow{};
    int m_CurrentCol{};

public:
    Sprite(const Texture &texture, const glm::vec3 &position, float scale, int row = 1, int col = 1);

    void animate(int spritesInSecond, int startRow = 0, int startCol = 0);

    void drawSprite(int row, int col);
};


#endif //SURVIVE_SPRITE_H
