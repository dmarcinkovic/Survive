//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_SPRITESRENDERER_H
#define SURVIVE_SPRITESRENDERER_H

#include <functional>
#include <entt.hpp>

#include "Components.h"
#include "SpritesShader.h"
#include "TexturedModel.h"
#include "Camera.h"
#include "Renderer2D.h"
#include "Transform3DComponent.h"
#include "SpriteSheetComponent.h"

namespace Survive
{
	class SpritesRenderer : public Renderer2D
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
