//
// Created by david on 05. 05. 2020..
//

#include "Display.h"
#include "Button.h"

Survive::Button::Button(const TexturedModel &texture, const glm::vec3 &position, float scaleX, float scaleY,
			   const glm::vec4 &color)
		: Entity(texture, position, glm::vec3{scaleX, scaleY, 1.0f}), m_Color(color), m_OriginalScaleX(scaleX),
		  m_OriginalScaleY(scaleY)
{
	auto[width, height] = Display::getWindowSize<float>();
	convertToScreenSpace(width, height);

	addMouseMoveListener();
	addWindowResizeListener();
}

void Survive::Button::convertToScreenSpace(float width, float height)
{
	int newX = static_cast<int>(convertPoint(m_Position.x, width));
	int newY = static_cast<int>(convertPoint(-m_Position.y, height));

	m_Center = glm::ivec2{newX, newY};
	m_Width = static_cast<int>(m_Scale.x * width);
	m_Height = static_cast<int>(m_Scale.y * height);
}

float Survive::Button::convertPoint(float point, float size)
{
	float scale = size / 2.0f;
	return scale * point + scale;
}

bool Survive::Button::isInsideButton(double x, double y) const
{
	int buttonX = m_Center.x - m_Width / 2;
	int buttonY = m_Center.y - m_Height / 2;

	return x >= buttonX && x <= buttonX + m_Width &&
		   y >= buttonY && y <= buttonY + m_Height;
}

void Survive::Button::addMouseMoveListener()
{
	auto mouseListener = [&](double x, double y) {
		if (isInsideButton(x, y))
		{
			m_Scale.x = m_OriginalScaleX * 1.02f;
			m_Scale.y = m_OriginalScaleY * 1.02f;
//			m_Text.scaleFor(1.02f);
		} else
		{
			m_Scale.x = m_OriginalScaleX;
			m_Scale.y = m_OriginalScaleY;
//			m_Text.scaleFor(1);
		}
	};

	EventHandler::addMouseMovedListener(mouseListener);
}

void Survive::Button::addWindowResizeListener()
{
	auto windowResizeListener = [&](int width, int height) {
		convertToScreenSpace(static_cast<float>(width), static_cast<float>(height));
	};

	EventHandler::addWindowResizeListener(windowResizeListener);
}

Survive::Text &Survive::Button::getText()
{
	return m_Text;
}

void Survive::Button::setText(const std::string &text, const Font &font, const glm::vec3 &textColor)
{
//	m_Text = Text(text, font, m_Position, textColor);
	m_Text.centerText();
}
