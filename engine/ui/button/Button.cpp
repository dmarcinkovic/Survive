//
// Created by david on 03. 05. 2020..
//

#include <iostream>

#include "Button.h"
#include "../../display/Display.h"

Button::Button(const Texture &texture, const glm::vec3 &position, float scaleX, float scaleY, const glm::vec4 &color)
        : Entity2D(texture, position, scaleX, scaleY), m_Color(color)
{
    auto[width, height] = Display::getWindowSize();
    convertToScreenSpace(width, height);

    auto windowResizeListener = [&](int width, int height)
    {
        convertToScreenSpace(static_cast<float>(width), static_cast<float>(height));
    };
    Display::addWindowResizeListener(windowResizeListener);

    addMouseListener();
    addMouseMovedListener();
}

void Button::addMouseListener()
{
    auto listener = std::mem_fn(&Button::mouseListener);
    auto mouseListener = std::bind_front(listener, this);

    Display::addMouseListener(mouseListener);
}

void Button::convertToScreenSpace(float width, float height)
{
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

void Button::mouseListener(int button, int action, double x, double y)
{
    if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT && isInsideButton(x, y))
    {
        std::cout << "Button pressed\n";
    }
}

void Button::mouseMovedListener(double x, double y)
{
    static const float scaleX = m_ScaleX;
    static const float scaleY = m_ScaleY;

    if (isInsideButton(x, y))
    {
        m_ScaleX = scaleX * 1.05f;
        m_ScaleY = scaleY * 1.05f;
    } else
    {
        m_ScaleY = scaleY;
        m_ScaleX = scaleX;
    }
}

void Button::addMouseMovedListener()
{
    auto listener = std::mem_fn(&Button::mouseMovedListener);
    auto mouseMovedListener = std::bind_front(listener, this);

    Display::addMouseMovedListener(mouseMovedListener);
}

