//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_SPRITE_H
#define SURVIVE_SPRITE_H


#include "../entity/Entity2D.h"

class Sprite : public Entity2D
{
private:
    int m_LastFrameIndex{};
    int m_CurrentFrameIndex{};
    double m_Time{};

public:
    const int m_Row, m_Col;
    int m_CurrentRow{}, m_CurrentCol{};
    bool m_Animate{};

    int m_SpritesInSecond{};

    Sprite(const Texture &texture, const glm::vec3 &position, float scale, int row = 1, int col = 1);

    void animate(int spritesInSecond, int startRow = 0, int startCol = 0);

    void drawSprite(int row, int col);

    void animate();
};


#endif //SURVIVE_SPRITE_H
