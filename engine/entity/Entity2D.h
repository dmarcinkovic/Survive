//
// Created by david on 27. 03. 2020..
//

#ifndef SURVIVE_ENTITY2D_H
#define SURVIVE_ENTITY2D_H


#include "../texture/Texture.h"

struct Entity2D
{
    Texture m_Texture;

    explicit Entity2D(const Texture &texture);
};


#endif //SURVIVE_ENTITY2D_H
