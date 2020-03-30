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
    const std::string m_Text;
    const Font m_Font;
    const char *textureAtlas;
    bool m_Centered{};
    glm::vec3 m_Color{};

    std::vector<float> m_Vertices;
    std::vector<float> m_TextureCoordinates;

public:
    Text(std::string text, Font font, const char *textureAtlasFile, const glm::vec3 &position,
         const glm::vec3 &color = glm::vec3{1, 1, 1}, float scale = 1.0);

    void loadTexture(Loader &loader);

    void centerText();

    const glm::vec3 &color() const;

private:
    Model calculateVertices(Loader &loader);

    void addVertices(const Character &character, float cursorX, float cursorY);

    void alignText(float start, float end);
};


#endif //SURVIVE_TEXT_H
