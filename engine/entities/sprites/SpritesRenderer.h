//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_SPRITESRENDERER_H
#define SURVIVE_SPRITESRENDERER_H

#include <functional>

#include "Components.h"
#include "entt.hpp"
#include "SpritesShader.h"
#include "TexturedModel.h"
#include "Camera.h"

namespace Survive
{
	class SpritesRenderer
	{
	private:
		SpritesShader m_Shader{};

	public:
		void render(entt::registry &registry, const Camera &camera) const;

	private:
		void loadUniforms(const Transform3DComponent &transform, const SpriteSheetComponent &sprite) const;

		static std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash>
		prepareEntities(entt::registry &registry);

		void renderSprites(const std::vector<entt::entity> &sprites, const entt::registry &registry,
						   const TexturedModel &texturedModel) const;
	};
}

#endif //SURVIVE_SPRITESRENDERER_H
