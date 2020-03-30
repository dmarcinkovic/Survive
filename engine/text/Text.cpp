//
// Created by david on 29. 03. 2020..
//

#include "Text.h"

#include <utility>

Text::Text(std::string text, Font font, const char *textureAtlasFile, const glm::vec3 &position, float scale)
        : Entity2D(), m_Text(std::move(text)), m_Font(std::move(font)), textureAtlas(textureAtlasFile)
{
    m_Position = position;
    m_Scale = scale;
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

        cursorX += character.m_Advance / 512; // TODO do not hard code this
    }

    return loader.loadToVao(m_Vertices, m_TextureCoordinates, 2);
}

void Text::addVertices(const Character &character, float cursorX, float cursorY)
{
    float minX = cursorX + character.m_XOffset / 512;
    float maxX = minX + character.m_Width / 512;
    float maxY = cursorY + character.m_YOffset / 512;
    float minY = maxY - character.m_Height / 512;

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

void Text::loadTexture(Loader &loader)
{
    m_Texture = Texture(calculateVertices(loader), loader.loadTexture(textureAtlas));
}
