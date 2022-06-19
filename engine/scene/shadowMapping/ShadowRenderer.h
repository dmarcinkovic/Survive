//
// Created by david on 22. 05. 2020..
//

#ifndef SURVIVE_SHADOWRENDERER_H
#define SURVIVE_SHADOWRENDERER_H

#include <vector>
#include <unordered_map>
#include <functional>
#include <entt.hpp>

#include "ShadowShader.h"
#include "TexturedModel.h"
#include "Camera.h"
#include "Light.h"
#include "Renderer3D.h"

namespace Survive
{
	class ShadowRenderer : public Renderer3D
	{
	private:
		ShadowShader m_ShadowShader{};

	public:
		void render(entt::registry &registry, const Light &light, const Camera &camera) const;

	private:
		static std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash>
		prepareEntities(entt::registry &registry);
	};
}

#endif //SURVIVE_SHADOWRENDERER_H
