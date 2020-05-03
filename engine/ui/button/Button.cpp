//
// Created by david on 03. 05. 2020..
//

#include "Button.h"

Button::Button(const Entity2D &entity2D)
    : m_Entity(entity2D)
{

}

const Entity2D &Button::getMEntity() const
{
    return m_Entity;
}
