//
// Created by david on 27. 12. 2020..
//

#ifndef SURVIVE_OUTLINERENDERER_H
#define SURVIVE_OUTLINERENDERER_H

#include <functional>
#include <unordered_map>

#include "OutlineShader.h"
#include "../texture/TexturedModel.h"
#include "../light/Light.h"
#include "../camera/Camera.h"
#include "../../ecs/entt.hpp"
#include "../components/Transform3DComponent.h"
#include "../components/RenderComponent.h"


class OutlineRenderer
{
private:
	static constexpr float SCALE = 1.04f;

	OutlineShader m_Shader;
	entt::entity m_Entity{};
	bool m_Render{};

public:
	void render(entt::registry &registry, const Camera &camera) const;

	void add3DObject(entt::registry &registry, entt::entity entity);

	void removeObject(entt::registry &registry);

private:
	static void setStencilFunctions();

	static void resetStencilFunctions();

	void loadUniforms(const Transform3DComponent &transform, const Camera &camera) const;

	static void prepareObject(const RenderComponent &renderComponent) ;

	static void finishRenderingObject();
};


#endif //SURVIVE_OUTLINERENDERER_H
