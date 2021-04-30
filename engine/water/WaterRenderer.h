//
// Created by david on 22. 02. 2021..
//

#ifndef SURVIVE_WATERRENDERER_H
#define SURVIVE_WATERRENDERER_H

#include <functional>

#include "../texture/Texture.h"
#include "WaterShader.h"
#include "../light/Light.h"
#include "../camera/Camera.h"
#include "WaterFbo.h"
#include "../../ecs/entt.hpp"
#include "../components/Components.h"

namespace Survive
{
	class WaterRenderer
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
		void prepareRendering(const Camera &camera) const;

		static void finishRendering();

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
