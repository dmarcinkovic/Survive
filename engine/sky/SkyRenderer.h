//
// Created by david on 25. 12. 2020..
//

#ifndef SURVIVE_SKYRENDERER_H
#define SURVIVE_SKYRENDERER_H


#include "SkyShader.h"
#include "../entity/Entity.h"
#include "../camera/Camera.h"
#include "../../ecs/entt.hpp"
#include "../components/Components.h"

class SkyRenderer
{
private:
	static constexpr float ROTATE_SPEED = 5.0f;

	SkyShader m_Shader;
	entt::entity m_Sky;

	float m_Rotation = 0;
	bool m_ShouldRender = false;

public:
	void render(entt::registry &registry, const Camera &camera, const glm::vec4 &plane = glm::vec4{}) const;

	void addSkyEntity(entt::entity sky);

	void rotateSky();

private:
	void prepareRendering(const RenderComponent &renderComponent) const;

	static void finishRendering();

	void loadUniforms(const Transform3DComponent &transform, const Camera &camera, const glm::vec4 &plane) const;
};


#endif //SURVIVE_SKYRENDERER_H
