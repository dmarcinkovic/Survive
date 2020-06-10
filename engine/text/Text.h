//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_TEXT_H
#define SURVIVE_TEXT_H

#include <string>
#include <vector>

#include "../entity/Entity2D.h"
#include "Font.h"

class Text : public Entity2D
{
private:
    constexpr static float PADDING = -15.0f;

    std::string m_Text;
    const Font m_Font;
    bool m_Centered{};
    glm::vec3 m_Color{};

    GLuint m_TextTexture, m_VboTexture{}, m_VboVertices{};

    glm::vec3 m_BorderColor;
    float m_BorderWidth{};

    std::vector<float> m_Vertices;
    std::vector<float> m_TextureCoordinates;

public:
    Text(std::string text, Font font, const glm::vec3 &position,
         const glm::vec3 &color = glm::vec3{1, 1, 1}, float scale = 1.0);

    void loadTexture(Loader &loader);

    void centerText();

    const glm::vec3 &color() const;

    const glm::vec3 &getMBorderColor() const;

    float getMBorderWidth() const;

    void addBorder(float borderWidth, const glm::vec3 &borderColor);

    void setText(std::string newText, Loader &loader);

private:
    void calculateTextureVertices();

    Model calculateVertices(Loader &loader);

    void addVertices(const Character &character, float cursorX, float cursorY);

    void alignText();

    std::pair<float, float> minMax() const;
};


#endif //SURVIVE_TEXT_H
