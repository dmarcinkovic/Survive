//
// Created by david on 22. 05. 2020..
//

#ifndef SURVIVE_SHADOWRENDERER_H
#define SURVIVE_SHADOWRENDERER_H

#include <vector>
#include <unordered_map>
#include <functional>

#include "ShadowShader.h"
#include "../light/Light.h"
#include "../camera/Camera.h"
#include "../../ecs/entt.hpp"
#include "../texture/TexturedModel.h"

class ShadowRenderer
{
private:
	ShadowShader m_ShadowShader{};
	std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash> m_Objects;

public:
	void render(entt::registry &registry, const Light &light, const Camera &camera) const;

	void add3DObject(entt::registry &registry, entt::entity entity);
};


#endif //SURVIVE_SHADOWRENDERER_H
