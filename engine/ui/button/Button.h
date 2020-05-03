//
// Created by david on 03. 05. 2020..
//

#ifndef SURVIVE_BUTTON_H
#define SURVIVE_BUTTON_H


#include "../../entity/Entity2D.h"

class Button
{
private:
    Entity2D m_Entity{};

public:
    explicit Button(const Entity2D &entity2D);

    [[nodiscard]] const Entity2D &getMEntity() const;
};


#endif //SURVIVE_BUTTON_H
