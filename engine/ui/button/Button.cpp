//
// Created by david on 05. 05. 2020..
//

#include "Button.h"
#include "../../display/Display.h"

Button::Button(const Texture &texture, const glm::vec3 &position, float scaleX, float scaleY, const glm::vec4 &color,
               const std::string &text, const Font &font, const glm::vec3 &textColor)
        : Entity2D(texture, position, scaleX, scaleY), m_Color(color), m_OriginalScaleX(scaleX),
          m_OriginalScaleY(scaleY), m_Text(text, font, position, textColor)
{
    auto[width, height] = Display::getWindowSize();
    convertToScreenSpace(width, height);

    addMouseMoveListener();
    addWindowResizeListener();

    m_Text.centerText();
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

void Button::addMouseMoveListener()
{
    auto mouseListener = [&](double x, double y)
    {
        if (isInsideButton(x, y))
        {
            m_ScaleX = m_OriginalScaleX * 1.02f;
            m_ScaleY = m_OriginalScaleY * 1.02f;
            m_Text.scaleFor(1.02f);
        } else
        {
            m_ScaleX = m_OriginalScaleX;
            m_ScaleY = m_OriginalScaleY;
            m_Text.scaleFor(1);
        }
    };

    Display::addMouseMovedListener(mouseListener);
}

void Button::addWindowResizeListener()
{
    auto windowResizeListener = [&](int width, int height)
    {
        convertToScreenSpace(static_cast<float>(width), static_cast<float>(height));
    };

    Display::addWindowResizeListener(windowResizeListener);
}

Text &Button::getText()
{
    return m_Text;
}
