//
// Created by david on 03. 05. 2020..
//

#ifndef SURVIVE_BUTTON_H
#define SURVIVE_BUTTON_H


#include "../../entity/Entity2D.h"

class Button : public Entity2D
{
public:
    explicit Button(const Texture &texture, const glm::vec3 &position, float scaleX, float scaleY);
};


#endif //SURVIVE_BUTTON_H
