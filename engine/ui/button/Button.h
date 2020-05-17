//
// Created by david on 05. 05. 2020..
//

#ifndef SURVIVE_BUTTON_H
#define SURVIVE_BUTTON_H

#include <glm/glm.hpp>

#include "../../entity/Entity.h"

struct Button : public Entity
{
    glm::vec4 m_Color;
    glm::ivec2 m_Center{};

    const float m_OriginalScaleX;
    const float m_OriginalScaleY;

    int m_Width{}, m_Height{};

    Button(const Texture &texture, const glm::vec3 &position, float scaleX, float scaleY, const glm::vec4 &color);

private:
    bool isInsideButton(double x, double y) const;

    static float convertPoint(float point, float size);

    void convertToScreenSpace(float width, float height);

    void addMouseMoveListener();

    void addWindowResizeListener();
};


#endif //SURVIVE_BUTTON_H
