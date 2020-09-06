//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_TEXT_H
#define SURVIVE_TEXT_H

#include <string>
#include <vector>

#include "../entity/Entity.h"
#include "Font.h"

class Text : public Entity
{
private:
    constexpr static float PADDING = 5.0f;

    const std::string m_Text;
    const Font m_Font;
    const char *textureAtlas;
    bool m_Centered{};
    glm::vec3 m_Color{};

    glm::vec3 m_BorderColor;
    float m_BorderWidth{};

    std::vector<float> m_Vertices;
    std::vector<float> m_TextureCoordinates;

public:
    Text(std::string text, Font font, const char *textureAtlasFile, const glm::vec3 &position,
         const glm::vec3 &color = glm::vec3{1, 1, 1}, float scale = 1.0);

    void loadTexture(Loader &loader);

    void centerText();

    const glm::vec3 &color() const;

    const glm::vec3 &getMBorderColor() const;

    float getMBorderWidth() const;

    void addBorder(float borderWidth, const glm::vec3 &borderColor);

private:
    Model calculateVertices(Loader &loader);

    void addVertices(const Character &character, float cursorX, float cursorY);

    void alignText();

    std::pair<float, float> minMax() const;
};


#endif //SURVIVE_TEXT_H
