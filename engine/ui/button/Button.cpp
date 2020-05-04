//
// Created by david on 03. 05. 2020..
//

#include <iostream>
#include "Button.h"
#include "../../display/Display.h"

Button::Button(const Texture &texture, const glm::vec3 &position, float scaleX, float scaleY, const glm::vec4 &color)
        : Entity2D(texture, position, scaleX, scaleY), m_Color(color)
{
    auto mouseListener = [&](int button, int action)
    {
        auto[x, y] = Display::getMousePosition();
        convertToScreenSpace();

        if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT && isInsideButton(x, y))
        {
            std::cout << "Inside button\n";
        }
    };

    Display::addMouseListener(mouseListener);
}

void Button::convertToScreenSpace()
{
    auto[width, height] = Display::getWindowSize();

    int newX = static_cast<int>(convertPoint(m_Position.x, width));
    int newY = static_cast<int>(convertPoint(-m_Position.y, height));

    m_Center = glm::ivec2{newX, newY};
    m_Width = static_cast<int>(m_ScaleX * width);
    m_Height = static_cast<int>(m_ScaleY * height);
}

float Button::convertPoint(float point, float size)
{
    float scale = size / 2.0f;
    return scale * point + scale;
}

bool Button::isInsideButton(double x, double y) const
{
    int buttonX = m_Center.x - m_Width / 2;
    int buttonY = m_Center.y - m_Height / 2;

    return x >= buttonX && x <= buttonX + m_Width &&
           y >= buttonY && y <= buttonY + m_Height;
}

