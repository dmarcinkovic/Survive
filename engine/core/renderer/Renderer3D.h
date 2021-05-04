//
// Created by david on 22. 05. 2020..
//

#ifndef SURVIVE_RENDERER3D_H
#define SURVIVE_RENDERER3D_H

#include "../../animations/renderer/AnimationRenderer.h"
#include "../../entities/water/WaterRenderer.h"
#include "../../entities/terrain/TerrainRenderer.h"
#include "../../entities/sky/SkyRenderer.h"
#include "../../entities/objects/ObjectRenderer.h"
#include "../../editor/mousePicking/MousePicking.h"
#include "../../editor/outline/OutlineRenderer.h"
#include "../../scene/gaussianBlur/BloomRenderer.h"

namespace Survive
{
	class Renderer3D
	{
	private:
		ObjectRenderer m_ObjectRenderer;
		TerrainRenderer m_TerrainRenderer;
		ShadowRenderer m_ShadowRenderer;
		AnimationRenderer m_AnimationRenderer;
		SkyRenderer m_SkyRenderer;
		OutlineRenderer m_OutlineRenderer;
		MousePicking m_MousePicking;
		WaterRenderer m_WaterRenderer;
		BloomRenderer m_BloomRenderer;

		const Light &m_Light;
		FrameBuffer m_FrameBuffer;
		const GLuint m_ShadowMap;

		glm::vec4 m_ReflectionCLippingPlane{};
		glm::vec4 m_RefractionCLippingPlane{};

	public:
		explicit Renderer3D(const Light &light);

		void render(entt::registry &registry, Camera &camera) const;

		void addSkyboxEntity(entt::entity sky);

		void addOutlineToObject(entt::registry &registry, entt::entity entity);

		void removeOutlineToObject(entt::registry &registry);

		void addShadow(entt::registry &registry, entt::entity entity);

		void renderScene(entt::registry &registry, Camera &camera, const glm::vec4 &plane = glm::vec4{}) const;

	private:
		void renderToWaterFrameBuffers(entt::registry &registry, Camera &camera) const;

		void renderWaterReflection(entt::registry &registry, Camera &camera) const;

		void renderWaterRefraction(entt::registry &registry, Camera &camera) const;
	};
}

#endif //SURVIVE_RENDERER3D_H
