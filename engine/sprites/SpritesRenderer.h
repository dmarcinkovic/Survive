//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_SPRITESRENDERER_H
#define SURVIVE_SPRITESRENDERER_H

#include <functional>

#include "../gui/GuiRenderer.h"
#include "SpritesShader.h"
#include "Sprite.h"
#include "../components/TransformComponent.h"

class SpritesRenderer
{
private:
	SpritesShader m_Shader{};

public:
	void render(entt::registry &registry) const;

private:
	static void animate(Sprite &sprite);

	void loadUniforms(const TransformComponent &transform, const Sprite &sprite) const;

	static std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash>
	prepareEntities(entt::registry &registry);

	void renderSprites(const std::vector<entt::entity> &sprites, entt::registry &registry,
					   const TexturedModel &texturedModel) const;
};


#endif //SURVIVE_SPRITESRENDERER_H
