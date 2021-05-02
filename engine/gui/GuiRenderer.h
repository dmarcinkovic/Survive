//
// Created by david on 28. 03. 2020..
//

#ifndef SURVIVE_GUIRENDERER_H
#define SURVIVE_GUIRENDERER_H

#include <functional>
#include <unordered_map>

#include "GuiShader.h"
#include "../../ecs/entt.hpp"
#include "../core/texture/TexturedModel.h"

namespace Survive
{
	class GuiRenderer
	{
	private:
		GuiShader m_Shader{};

	public:
		void render(entt::registry &registry) const;

	private:
		static std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash>
		prepareEntities(entt::registry &registry);

		void renderGuis(const std::vector<entt::entity> &guis, const entt::registry &registry,
						const TexturedModel &texturedModel) const;
	};
}

#endif //SURVIVE_GUIRENDERER_H
