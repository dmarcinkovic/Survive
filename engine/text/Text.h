//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_TEXT_H
#define SURVIVE_TEXT_H

#include <string>

#include "../entity/Entity2D.h"

struct Text : public Entity2D
{
    const std::string m_Text;

    Text(std::string text, const Texture &texture, const glm::vec3 &position, float scale = 1.0);
};


#endif //SURVIVE_TEXT_H
