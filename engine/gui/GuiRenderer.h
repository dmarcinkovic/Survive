//
// Created by david on 28. 03. 2020..
//

#ifndef SURVIVE_GUIRENDERER_H
#define SURVIVE_GUIRENDERER_H

#include <unordered_map>

#include "../renderer/Loader.h"
#include "../entity/Entity2D.h"
#include "../texture/Texture.h"
#include "GuiShader.h"

class GuiRenderer
{
private:
    GuiShader m_Shader{};
    std::unordered_map<Texture, std::vector<Entity2D>, TextureHash> m_Guis;

public:
    void renderGui() const;

    void addGui(const Entity2D &entity2D) noexcept;

};


#endif //SURVIVE_GUIRENDERER_H
