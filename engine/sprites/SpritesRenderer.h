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
	std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash> m_Sprites;

public:
	void renderSprite(entt::registry &registry) const;

	void addSprite(const entt::registry &registry, entt::entity entity) noexcept;

private:
	static void animate(Sprite &sprite);

	void loadUniforms(const TransformComponent &transform, const Sprite &sprite) const;
};


#endif //SURVIVE_SPRITESRENDERER_H
