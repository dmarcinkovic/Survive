//
// Created by david on 25. 12. 2020..
//

#ifndef SURVIVE_SKYRENDERER_H
#define SURVIVE_SKYRENDERER_H


#include "SkyShader.h"
#include "entt.hpp"
#include "Components.h"
#include "Camera.h"
#include "Renderer3D.h"

namespace Survive
{
	class SkyRenderer : public Renderer3D
	{
	private:
		SkyShader m_Shader;

	public:
		void render(entt::registry &registry, const Camera &camera, const glm::vec4 &plane = glm::vec4{}) const;

	private:
		static void prepareRenderingSky(const SkyboxComponent &skyComponent) ;

		static void finishRenderingSky();

		void loadUniforms(const entt::registry &registry, const Transform3DComponent &transform, const Camera &camera,
						  const glm::vec4 &plane) const;
	};
}

#endif //SURVIVE_SKYRENDERER_H
