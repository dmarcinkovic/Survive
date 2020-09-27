//
// Created by david on 28. 03. 2020..
//

#ifndef SURVIVE_GUIRENDERER_H
#define SURVIVE_GUIRENDERER_H

#include <functional>
#include <unordered_map>

#include "../renderer/Loader.h"
#include "../entity/Entity.h"
#include "../texture/TexturedModel.h"
#include "GuiShader.h"

class GuiRenderer
{
private:
    GuiShader m_Shader{};
    std::unordered_map<TexturedModel, std::vector<std::reference_wrapper<Entity>>, TextureHash> m_Entities;

public:
    void render() const;

    void addEntity(Entity &entity2D) noexcept;
};


#endif //SURVIVE_GUIRENDERER_H
