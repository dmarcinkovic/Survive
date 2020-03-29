//
// Created by david on 28. 03. 2020..
//

#ifndef SURVIVE_GUIRENDERER_H
#define SURVIVE_GUIRENDERER_H

#include <functional>
#include <unordered_map>

#include "../renderer/Loader.h"
#include "../entity/Entity2D.h"
#include "../texture/Texture.h"
#include "GuiShader.h"

class GuiRenderer
{
private:
    GuiShader m_Shader{};
    std::unordered_map<Texture, std::vector<std::reference_wrapper<Entity2D>>, TextureHash> m_Entities;

public:
    void render() const;

    void addEntity(Entity2D &entity2D) noexcept;

private:
    void prepareRendering() const;

    void prepareEntity(const Texture &texture) const;

    static void finishRenderingEntity();

    static void finishRendering();
};


#endif //SURVIVE_GUIRENDERER_H
