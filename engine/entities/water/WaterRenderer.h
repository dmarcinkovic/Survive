//
// Created by david on 22. 02. 2021..
//

#ifndef SURVIVE_WATERRENDERER_H
#define SURVIVE_WATERRENDERER_H

#include <functional>

#include "entt.hpp"
#include "WaterShader.h"
#include "WaterFbo.h"
#include "Components.h"
#include "Light.h"

namespace Survive
{
	class WaterRenderer : public Renderer3D
	{
	private:
		WaterShader m_Shader;
		WaterFbo m_Fbo;

	public:
		void render(entt::registry &registry, const Camera &camera, const Light &light) const;

		void bindReflectionFrameBuffer() const;

		void bindRefractionFrameBuffer() const;

		[[nodiscard]] static bool shouldRender(entt::registry &registry);

	private:
		void prepareRenderingWater(const Camera &camera) const;

		static void finishRenderingWater();

		static void loadMoveFactor(const WaterShader &shader, MoveComponent &moveComponent);

		void loadUniforms(const Camera &camera, const Transform3DComponent &transform, MoveComponent &moveComponent,
						  const Light &light) const;

		static void
		bindTextures(const TexturedComponent &textures, const Texture &reflectionTexture,
					 const Texture &refractionTexture,
					 const Texture &refractionDepthMap);
	};
}


#endif //SURVIVE_WATERRENDERER_H
