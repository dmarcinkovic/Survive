//
// Created by david on 17. 05. 2020..
//

#ifndef SURVIVE_OBJECTRENDERER_H
#define SURVIVE_OBJECTRENDERER_H

#include <unordered_map>
#include <functional>

#include "ObjectShader.h"
#include "../texture/TexturedModel.h"
#include "../entity/Entity.h"
#include "../camera/Camera.h"
#include "../light/Light.h"
#include "Object3D.h"
#include "../gui/GuiRenderer.h"

class ObjectRenderer
{
private:
	ObjectShader m_Shader;
	std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash> m_Objects;

	const Light &m_Light;

public:
	explicit ObjectRenderer(const Light &light);

	void render(entt::registry &registry, const Camera &camera, GLuint shadowMap,
				const glm::vec4 &plane = glm::vec4{}) const;

	void add3DObject(entt::registry &registry, entt::entity entity);

	void add3DObject(Object3D &entity);

private:
	void renderScene(entt::registry &registry, const std::vector<entt::entity> &objects, const Camera &camera) const;

	void loadUniforms(const Camera &camera, GLuint shadowMap, const glm::vec4 &plane) const;

	void loadObjectUniforms(entt::registry &registry, entt::entity, const Camera &camera) const;
};

#endif //SURVIVE_OBJECTRENDERER_H
