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

class AnimationRenderer
{
private:
	AnimationShader m_Shader;
	std::unordered_map<TexturedModel, std::vector<std::reference_wrapper<AnimatedObject>>, TextureHash> m_Objects;

	const Light &m_Light;

public:
	explicit AnimationRenderer(const Light &light);

	void render(const Camera &camera) const;

	void addAnimatedModel(AnimatedObject &entity);

private:
	void renderScene(const std::vector<std::reference_wrapper<AnimatedObject>> &objects, const Camera &camera) const;
};

#endif //SURVIVE_ANIMATIONRENDERER_H
