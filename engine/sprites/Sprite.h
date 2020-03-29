//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_SPRITE_H
#define SURVIVE_SPRITE_H


#include "../entity/Entity2D.h"

class Sprite : public Entity2D
{
private:
    int row;
    int col;

public:
    Sprite(const Texture &texture, const glm::vec3 &position, float scale, int row = 0, int col = 0);
};


#endif //SURVIVE_SPRITE_H
