//
// Created by david on 25. 12. 2020..
//

#ifndef SURVIVE_SKYRENDERER_H
#define SURVIVE_SKYRENDERER_H


#include "SkyShader.h"
#include "entt.hpp"
#include "Components.h"
#include "Camera.h"

namespace Survive
{
	class SkyRenderer
	{
	private:
		SkyShader m_Shader;
		entt::entity m_Sky{};

		bool m_ShouldRender = false;

	public:
		void render(const entt::registry &registry, const Camera &camera, const glm::vec4 &plane = glm::vec4{}) const;

		void addSkyEntity(entt::entity sky);

		void removeSkyEntity();

	private:
		void prepareRendering(const Render3DComponent &renderComponent) const;

		static void finishRendering();

		void loadUniforms(const entt::registry &registry, const Transform3DComponent &transform, const Camera &camera,
						  const glm::vec4 &plane) const;
	};
}

#endif //SURVIVE_SKYRENDERER_H
