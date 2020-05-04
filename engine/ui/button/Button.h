//
// Created by david on 03. 05. 2020..
//

#ifndef SURVIVE_BUTTON_H
#define SURVIVE_BUTTON_H

#include <glm/glm.hpp>

#include "../../entity/Entity2D.h"

class Button : public Entity2D
{
private:
    glm::ivec2 m_Center{};
    int m_Width{}, m_Height{};

public:
    glm::vec4 m_Color;

    Button(const Texture &texture, const glm::vec3 &position, float scaleX, float scaleY,
                    const glm::vec4 &color);

private:
    void convertToScreenSpace();

    static float convertPoint(float point, float size);

    [[nodiscard]] bool isInsideButton(double x, double y) const;
};


#endif //SURVIVE_BUTTON_H
