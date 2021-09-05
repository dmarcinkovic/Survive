//
// Created by david on 29. 03. 2020..
//

#include "Text.h"

#include <utility>
#include <iostream>

Survive::Text::Text(std::string text, Font font, const glm::vec3 &position,
					const glm::vec3 &color, float scale)
		: Entity(), m_Text(std::move(text)), m_Font(std::move(font)), m_Color(color),
		  m_BorderColor(color), m_TextTexture(font.getTexture())
{
	m_Position = position;
	m_Scale.x = m_Scale.y = scale;
}

Survive::Text::Text(std::string text, Survive::Font font)
	: Entity(), m_Text(std::move(text)), m_Font(std::move(font))
{

}

Survive::Model Survive::Text::calculateVertices(Loader &loader)
{
	m_Vertices.clear();
	m_TextureCoordinates.clear();

	calculateTextureVertices();

	return loader.loadToVao(m_Vertices, m_TextureCoordinates, 2);
}

void Survive::Text::calculateTextureVertices()
{
	float cursorX = m_Position.x;
	float cursorY = m_Position.y;

	for (char c : m_Text)
	{
		const Character &character = m_Font.getCharacter(c);

		addVertices(character, cursorX, cursorY);

		auto const &textureCoordinates = character.m_TextureCoords;
		m_TextureCoordinates.insert(m_TextureCoordinates.end(),
									textureCoordinates.begin(), textureCoordinates.end());

		cursorX += character.m_Advance / character.m_ScaleW + PADDING / character.m_ScaleW;
	}

	if (m_Centered) alignText();
}

void Survive::Text::addVertices(const Character &character, float cursorX, float cursorY)
{
	float minX = cursorX + character.m_XOffset / character.m_ScaleW;
	float maxX = minX + character.m_Width / character.m_ScaleW;
	float maxY = cursorY + character.m_YOffset / character.m_ScaleH;
	float minY = maxY - character.m_Height / character.m_ScaleH;

	m_Vertices.emplace_back(minX);
	m_Vertices.emplace_back(maxY);
	m_Vertices.emplace_back(minX);
	m_Vertices.emplace_back(minY);
	m_Vertices.emplace_back(maxX);
	m_Vertices.emplace_back(minY);
	m_Vertices.emplace_back(maxX);
	m_Vertices.emplace_back(minY);
	m_Vertices.emplace_back(maxX);
	m_Vertices.emplace_back(maxY);
	m_Vertices.emplace_back(minX);
	m_Vertices.emplace_back(maxY);
}

void Survive::Text::loadTexture(Loader &loader)
{
	m_Texture = TexturedModel(calculateVertices(loader), m_TextTexture);
}

void Survive::Text::centerText()
{
	m_Centered = true;
}

void Survive::Text::setText(std::string newText, Loader &loader)
{
	m_Text = std::move(newText);

	m_TextureCoordinates.clear();
	m_Vertices.clear();

	calculateTextureVertices();

	loader.updateFloatData(m_Vertices, m_TextureCoordinates, m_Texture.vaoID());
	m_Texture.setVertexCount(static_cast<int>(m_Vertices.size()) / 2);
}

const glm::vec3 &Survive::Text::color() const
{
	return m_Color;
}

void Survive::Text::alignText()
{
	float startX = m_Vertices.front();
	float endX = m_Vertices[m_Vertices.size() - 4];

	auto[startY, endY] = minMax();

	float middleX = (endX - startX) / 2;
	float middleY = (endY - startY) / 2;

	for (int i = 0; i < m_Vertices.size(); i += 2)
	{
		m_Vertices[i] -= middleX;
		m_Vertices[i + 1] += middleY;
	}
}

std::pair<float, float> Survive::Text::minMax() const
{
	float max = -1.0f;
	float min = std::numeric_limits<float>::infinity();

	for (int i = 1; i < m_Vertices.size(); i += 2)
	{
		min = std::min(min, m_Vertices[i]);
		max = std::max(max, m_Vertices[i]);
	}

	return {min, max};
}

void Survive::Text::addBorder(float borderWidth, const glm::vec3 &borderColor)
{
	m_BorderWidth = borderWidth;
	m_BorderColor = borderColor;
}

const glm::vec3 &Survive::Text::getBorderColor() const
{
	return m_BorderColor;
}

float Survive::Text::getBorderWidth() const
{
	return m_BorderWidth;
}

float Survive::Text::getScale() const
{
	return m_Scale.x;
}

void Survive::Text::scaleFor(float scaleFactor)
{
	m_Scale.x = m_Scale.y * scaleFactor;
}

const Survive::TexturedModel &Survive::Text::getTexturedModel() const
{
	return m_Texture;
}
