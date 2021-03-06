//
// Created by david on 17. 05. 2020..
//

#ifndef SURVIVE_ANIMATIONRENDERER_H
#define SURVIVE_ANIMATIONRENDERER_H

#include <unordered_map>
#include <functional>

#include "../../texture/TexturedModel.h"
#include "../../entity/Entity.h"
#include "../../camera/Camera.h"
#include "../../light/Light.h"
#include "AnimationShader.h"
#include "../../objects/ObjectShader.h"
#include "../animation/AnimatedObject.h"
#include "../../../ecs/entt.hpp"

class AnimationRenderer
{
private:
	AnimationShader m_Shader;
	std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash> m_Objects;

	const Light &m_Light;

public:
	explicit AnimationRenderer(const Light &light);

	void render(entt::registry &registry, const Camera &camera, const glm::vec4 &plane = glm::vec4{}) const;

	void addAnimatedModel(entt::registry &registry, entt::entity);

private:
	void renderScene(entt::registry &registry, const std::vector<entt::entity> &objects, const Camera &camera) const;
};

#endif //SURVIVE_ANIMATIONRENDERER_H
