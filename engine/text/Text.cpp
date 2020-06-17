//
// Created by david on 29. 03. 2020..
//

#include "Text.h"

#include <utility>
#include <iostream>

Text::Text(std::string text, Font font, const glm::vec3 &position,
           const glm::vec3 &color, float scale)
        : Entity2D(), m_Text(std::move(text)), m_Font(std::move(font)), m_Color(color),
          m_BorderColor(color), m_TextTexture(font.getMTextureId())
{
    m_Position = position;
    m_ScaleX = scale;
    m_ScaleY = scale;
}

Text::Text()
    : Entity2D()
{

}

Model Text::calculateVertices(Loader &loader)
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

    return loader.loadToVao(m_Vertices, m_TextureCoordinates, 2);
}

void Text::addVertices(const Character &character, float cursorX, float cursorY)
{
    float minX = cursorX + character.m_XOffset / character.m_ScaleW;
    float maxX = minX + character.m_Width / character.m_ScaleW;
    float maxY = cursorY + character.m_YOffset / character.m_ScaleH;
    float minY = maxY - character.m_Height / character.m_ScaleH;

    m_Vertices.emplace_back(minX * m_ScaleX);
    m_Vertices.emplace_back(maxY * m_ScaleY);
    m_Vertices.emplace_back(minX * m_ScaleX);
    m_Vertices.emplace_back(minY * m_ScaleY);
    m_Vertices.emplace_back(maxX * m_ScaleX);
    m_Vertices.emplace_back(minY * m_ScaleY);
    m_Vertices.emplace_back(maxX * m_ScaleX);
    m_Vertices.emplace_back(minY * m_ScaleY);
    m_Vertices.emplace_back(maxX * m_ScaleX);
    m_Vertices.emplace_back(maxY * m_ScaleY);
    m_Vertices.emplace_back(minX * m_ScaleX);
    m_Vertices.emplace_back(maxY * m_ScaleY);
}

void Text::loadTexture(Loader &loader)
{
    m_Texture = Texture(calculateVertices(loader), m_TextTexture);
}

void Text::centerText()
{
    m_Centered = true;
}

const glm::vec3 &Text::color() const
{
    return m_Color;
}

void Text::alignText()
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

std::pair<float, float> Text::minMax() const
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

void Text::addBorder(float borderWidth, const glm::vec3 &borderColor)
{
    m_BorderWidth = borderWidth;
    m_BorderColor = borderColor;
}

const glm::vec3 &Text::getMBorderColor() const
{
    return m_BorderColor;
}

float Text::getMBorderWidth() const
{
    return m_BorderWidth;
}

float Text::getScale() const
{
    return m_ScaleX;
}

void Text::scaleFor(float scaleFactor)
{
    m_ScaleX = m_ScaleY * scaleFactor;
}

