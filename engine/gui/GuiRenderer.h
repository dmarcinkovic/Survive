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
#include "../../ecs/entt.hpp"

class GuiRenderer
{
private:
	GuiShader m_Shader{};
	std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash> m_Entities;

public:
	void render(const entt::registry &registry) const;

	void addEntity(const entt::registry &registry, entt::entity entity) noexcept;
};


#endif //SURVIVE_GUIRENDERER_H
