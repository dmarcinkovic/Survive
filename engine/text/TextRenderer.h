//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_TEXTRENDERER_H
#define SURVIVE_TEXTRENDERER_H

#include "../gui/GuiRenderer.h"
#include "TextShader.h"
#include "Text.h"

class TextRenderer : public GuiRenderer
{
private:
    const std::vector<float> m_Vertices = {-0.5, 0.5, -0.5, -0.5, 0.5, -0.5,
                                           0.5, -0.5, 0.5, 0.5, -0.5, 0.5};
    const std::vector<float> m_TextureCoords = {0.259766, 0.222656, 0.259766, 0.125, 0.345703, 0.125,
                                                0.345703, 0.125, 0.345703, 0.222656, 0.259766, 0.222656};

    TextShader m_Shader{};
    std::unordered_map<Texture, std::vector<std::reference_wrapper<Text>>, TextureHash> m_Texts;
    const Model m_Model;

public:
    explicit TextRenderer(Loader &loader);

    void renderText() const;

    void addText(Text &text);

    const Model &getModel() const;
};


#endif //SURVIVE_TEXTRENDERER_H
