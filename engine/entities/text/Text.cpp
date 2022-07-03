//
// Created by david on 29. 03. 2020..
//

#include <utility>

#include "Text.h"

Survive::Text::Text(std::string text, Font font)
		: m_Text(std::move(text)), m_Font(std::move(font))
{
	m_Text.reserve(512);
}

Survive::Text::Text()
{
	m_Text.reserve(512);
}

Survive::Text::Text(std::string text, Font font, float lineSpacing, bool centerText, bool addBorder,
					float borderWidth, glm::vec3 borderColor)
		: m_Text(std::move(text)), m_Font(std::move(font)), m_LineSpacing(lineSpacing), m_Centered(centerText),
		  m_AddBorder(addBorder), m_BorderWidth(borderWidth), m_BorderColor(borderColor)
{
	m_Text.reserve(512);
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
	float cursorX = 0;
	float cursorY = 0;

	for (char c: m_Text)
	{
		if (c == '\n')
		{
			cursorY -= m_LineSpacing * (m_Font.getHeight() / m_Font.getScaleHeight());
			cursorX = 0;
			continue;
		}

		const Character &character = m_Font.getCharacter(c);

		addVertices(character, cursorX, cursorY);

		auto const &textureCoordinates = character.m_TextureCoords;
		m_TextureCoordinates.insert(m_TextureCoordinates.end(),
									textureCoordinates.begin(), textureCoordinates.end());

		cursorX += character.m_Advance / character.m_ScaleW + PADDING / character.m_ScaleW;
	}

	if (m_Centered)
	{
		alignText();
	}
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
	m_Model = TexturedModel(calculateVertices(loader), m_Font.getTexture());
}

void Survive::Text::centerText()
{
	m_Centered = true;
}

void Survive::Text::setText(std::string newText, Loader &loader)
{
	m_Text = std::move(newText);
	m_Text.reserve(512);

	if (!m_Font.isFontLoaded())
	{
		return;
	}

	m_TextureCoordinates.clear();
	m_Vertices.clear();

	calculateTextureVertices();

	if (!m_Model.isValidTexture())
	{
		m_Model = TexturedModel(calculateVertices(loader), m_Font.getTexture());
	} else
	{
		loader.updateFloatData(m_Vertices, m_TextureCoordinates, m_Model.vaoID());
	}

	m_Model.setVertexCount(static_cast<int>(m_Vertices.size()) / 2);
}

void Survive::Text::alignText()
{
	float startX = m_Vertices.front();
	float endX = m_Vertices[m_Vertices.size() - 4];

	auto [startY, endY] = minMax();

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
	return m_AddBorder ? m_BorderWidth : 0;
}

const Survive::TexturedModel &Survive::Text::getModel() const
{
	return m_Model;
}

void Survive::Text::setFont(const Font &font)
{
	m_Font = font;
}
