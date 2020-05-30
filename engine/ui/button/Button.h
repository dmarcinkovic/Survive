//
// Created by david on 05. 05. 2020..
//

#ifndef SURVIVE_BUTTON_H
#define SURVIVE_BUTTON_H

#include <glm/glm.hpp>
#include <string>

#include "../../entity/Entity2D.h"
#include "../../text/Font.h"
#include "../../text/Text.h"

class Renderer2D;

struct Button : public Entity2D
{
private:
    Text m_Text;

public:
    glm::vec4 m_Color;
    glm::ivec2 m_Center{};

    const float m_OriginalScaleX;
    const float m_OriginalScaleY;

    int m_Width{}, m_Height{};

    Button(const Texture &texture, const glm::vec3 &position, float scaleX, float scaleY, const glm::vec4 &color,
           const std::string &text, const Font &font, const glm::vec3 &textColor = glm::vec3{0, 0, 0});

    Text &getText();

private:
    [[nodiscard]] bool isInsideButton(double x, double y) const;

    static float convertPoint(float point, float size);

    void convertToScreenSpace(float width, float height);

    void addMouseMoveListener();

    void addWindowResizeListener();
};


#endif //SURVIVE_BUTTON_H
