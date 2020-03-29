//
// Created by david on 29. 03. 2020..
//

#include "Text.h"

#include <utility>

Text::Text(std::string text, Font font, const Texture &texture, const glm::vec3 &position, float scale)
        : Entity2D(texture, position, scale), m_Text(std::move(text)), m_Font(std::move(font))
{
    calculateVertices();
}

void Text::calculateVertices()
{
    float cursorX = m_Position.x;
    float cursorY = m_Position.y;

    for (char c : m_Text)
    {
        const Character &character = m_Font.getCharacter(c);

        addVertices(character, cursorX, cursorY);

        cursorX += character.m_Advance / 512; // TODO do not hard code this
    }
}

void Text::addVertices(const Character &character, float cursorX, float cursorY)
{
    float minX = cursorX + character.m_XOffset / 512;
    float maxX = minX + character.m_Width / 512;
    float maxY = cursorY + character.m_YOffset / 512;
    float minY = maxY - character.m_Height / 512;

    vertices.emplace_back(minX);
    vertices.emplace_back(maxY);
    vertices.emplace_back(minX);
    vertices.emplace_back(minY);
    vertices.emplace_back(maxX);
    vertices.emplace_back(minY);
    vertices.emplace_back(maxX);
    vertices.emplace_back(minY);
    vertices.emplace_back(maxX);
    vertices.emplace_back(maxY);
    vertices.emplace_back(minX);
    vertices.emplace_back(maxY);
}
