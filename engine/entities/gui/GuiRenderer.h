//
// Created by david on 28. 03. 2020..
//

#ifndef SURVIVE_GUIRENDERER_H
#define SURVIVE_GUIRENDERER_H

#include <functional>
#include <unordered_map>
#include <entt.hpp>

#include "GuiShader.h"
#include "Camera.h"
#include "TexturedModel.h"
#include "Renderer2D.h"

namespace Survive
{
	class GuiRenderer : public Renderer2D
	{
	private:
		GuiShader m_Shader{};

	public:
		void render(entt::registry &registry, const Camera &camera) const;

	private:
		static std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash>
		prepareEntities(entt::registry &registry);

		void renderGuis(const std::vector<entt::entity> &guis, const entt::registry &registry,
						const TexturedModel &texturedModel) const;
	};
}

#endif //SURVIVE_GUIRENDERER_H
